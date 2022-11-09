#
# Daniel Loftus and Andrew Robinson
# Drone Programming
# Project 1 Part 2
#
###################################################################################################################

from dronekit import connect, VehicleMode, LocationGlobal, LocationGlobalRelative
from pymavlink import mavutil # Needed for command message definitions
import time
import math


#Set up option parsing to get connection string
import argparse
parser = argparse.ArgumentParser(description='Control Copter and send commands in GUIDED mode ')
parser.add_argument('--connect',
                   help="Vehicle connection target string. If not specified, SITL automatically started and used.")
args = parser.parse_args()

connection_string = args.connect
sitl = None

######################################################################################################################

#Start SITL if no connection string specified
if not connection_string:
    import dronekit_sitl
    sitl = dronekit_sitl.start_default()
    connection_string = sitl.connection_string()


# Connect to the Vehicle
print('Connecting to vehicle on: %s' % connection_string)
vehicle = connect(connection_string, wait_ready=True)

###################################################################################################################

###################################################################################################################
# Set the vehilce home location
def Set_Home():

    msg = vehicle.message_factory.command_long_encode(
        0, 0,
        mavutil.mavlink.MAV_CMD_DO_SET_HOME,
        0,  #confirmation
        1,  #1 for current location set as home, 2 for custon set by param 5-7
        0,0,0,0,0,0)
    time.sleep(2)
    vehicle.send_mavlink(msg)

###################################################################################################################
def Arm_Motors():

    print("Basic pre-arm checks")
    # Don't try to arm until autopilot is ready
    while not vehicle.is_armable:
        print(" Waiting for vehicle to initialise...")
        time.sleep(1)

    print("Arming Motors")
    # Copter should arm in GUIDED mode
    vehicle.mode = VehicleMode("GUIDED")
    vehicle.armed = True


    # Confirm vehicle armed before attempting to take off
    while not vehicle.armed:
        print(" Waiting for arming...")
        time.sleep(1)

    # print("ARM STATUS", vehicle.armed)

###################################################################################################################
def Define_Takeoff(set_altitude):

    msg = vehicle.message_factory.command_long_encode(
        0, 0,
        mavutil.mavlink.MAV_CMD_NAV_TAKEOFF,
        0,              #confirmation
        0,0,0,0,0,0,
        set_altitude)    #Number corresponds to height for take off

    time.sleep(2)

    vehicle.send_mavlink(msg)

    while True:
        print(" Altitude: ", vehicle.location.global_relative_frame.alt)
        # Break and return from function just below target altitude.
        if vehicle.location.global_relative_frame.alt >= set_altitude * 0.95:
            print("Reached target altitude")
            break
        time.sleep(1)

###################################################################################################################
#send_ned_velocity GO TO BY SPEED TO A SPECIFIC DIRECTION
def send_ned_velocity(velocity_x, velocity_y, velocity_z, duration):
    """
    Move vehicle in direction based on specified velocity vectors
    """
    msg = vehicle.message_factory.set_position_target_local_ned_encode(
        0,       # time_boot_ms (not used)
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_FRAME_LOCAL_NED, # frame
        0b0000111111000111, # type_mask (only velocity components enabled)
        0, 0, 0, # x, y, z positions (not used)
        velocity_x, velocity_y, velocity_z, # x, y, z velocity in m/s
        0, 0, 0, # x, y, z acceleration (not supported yet, ignored in GCS_Mavlink)
        0, 0)    # yaw, yaw_rate (not supported yet, ignored in GCS_Mavlink)

# send command to vehicle on 1 Hz cycle
    for x in range(0,duration):
        vehicle.send_mavlink(msg)
        time.sleep(1)

###################################################################################################################
def waypoint_Global(LAT, LON, ALT, Delay):

    msg = vehicle.master.mav.command_long_encode(
        0, 0,
        mavutil.mavlink.MAV_CMD_NAV_WAYPOINT,
        0, #confirmation
        Delay,
        0,0,0,
        LAT,
        LON,
        ALT)

    time.sleep(1)

    vehicle.send_mavlink(msg)

###################################################################################################################
def global_Waypoint(lat, lon, alt, delay):

    msg = vehicle.message_factory.mission_item_send(
        0,       # time_boot_ms (not used)
        0, 0,    # target system, target component
        mavutil.mavlink.MAV_FRAME_GLOBAL_RELATIVE_ALT, # frame
        mavutil.mavlink.MAV_CMD_NAV_WAYPOINT, # type_mask
        2,
        0,
        delay, #PARAM 1
        0,     #PARAM 2
        0,     #PARAM 3
        0,     #PARAM 4
        lat,   #PARAM 5
        lon,   #PARAM 6
        alt)   #PARAM 7

    time.sleep(2)

###################################################################################################################
def loiter(Wait):
    msg = vehicle.message_factory.command_long_encode(
        0, 0,
        mavutil.mavlink.MAV_CMD_NAV_LOITER_TIME,
        0,              #confirmation
        Wait,0,0,0,0,0,0)    #Number corresponds to height for take off

    time.sleep(2)

    vehicle.send_mavlink(msg)


###################################################################################################################
print("----------------------------------------------------")
print("Setting Home Position")
print("----------------------------------------------------")
Set_Home()
time.sleep(2)

Arm_Motors();

print("----------------------------------------------------")
print("Taking Off from A to location B")
print("----------------------------------------------------")
Define_Takeoff(10)
time.sleep(2)

print("----------------------------------------------------")
print("Loiter at location B for 10 seconds")
print("----------------------------------------------------")
loiter(10)
time.sleep(2)

print("----------------------------------------------------")
print("Going to location C")
print("----------------------------------------------------")
global_Waypoint(-35.3629, 149.168, 10, 1)
time.sleep(60)

print("----------------------------------------------------")
print("Loiter at location C for 5 seconds")
print("----------------------------------------------------")
loiter(5)
time.sleep(2)

print("----------------------------------------------------")
print("Going to location D")
print("----------------------------------------------------")
global_Waypoint(-35.3607, 149.168, 10, 1)
time.sleep(60)

print("----------------------------------------------------")
print("Loiter at location D for 5 seconds")
print("----------------------------------------------------")
loiter(5)
time.sleep(2)

print("----------------------------------------------------")
print("Going to location E")
print("----------------------------------------------------")
global_Waypoint(-35.3607, 149.165, 5, 1)
time.sleep(60)

print("----------------------------------------------------")
print("Going to location A")
print("----------------------------------------------------")
global_Waypoint(-35.3633, 149.165, 1, 1)
time.sleep(60)

print("----------------------------------------------------")
print("Returning Home")
print("----------------------------------------------------")
vehicle.mode = VehicleMode("RTL")
time.sleep(60)

###################################################################################################################

###################################################################################################################
# Close vehicle object before exiting script
print("Close vehicle object")
vehicle.close()

# Shut down simulator if it was started.
if sitl:
    sitl.stop()

###################################################################################################################
###################################################################################################################
