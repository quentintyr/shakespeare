#!/usr/bin/env python3
from networktables import NetworkTables
import json
import time
import os

print("Connecting at 10.12.34.2")
NetworkTables.initialize(server='10.12.34.2')
table = NetworkTables.getTable('Dashboard')

print("started bridge")
print("/home/lvuser/deploy/status.json")

while True:
    try:
        data = {
            'batteryVoltage': table.getNumber('Battery', 0),
            'robotMode': table.getString('RobotMode', 'unknown'),
            'USSensorLeft': table.getNumber('USSensorLeft', 0),
            'USSensorRight': table.getNumber('USSensorRight', 0),
            'IRSensorLeft': table.getNumber('IRSensorLeft', 0),
            'IRSensorRight': table.getNumber('IRSensorRight', 0),
            'lidarDistance': table.getNumber('LidarDistance', 0),
            'lidarStatus': table.getString('LidarStatus', 'disconnected'),
            'elevatorPosition': table.getString('ElevatorPosition', '0mm'),
            'carriagePosition': table.getString('CarriagePosition', 'home'),
            'gripperStatus': table.getString('GripperStatus', 'open'),
            'extenderStatus': table.getString('ExtenderStatus', 'idle'),
            'extenderLength': table.getNumber('ExtenderLength', 0),
            'lineFollowerSensor': table.getString('LineFollowerSensor', 'not on line'),
            'connected': NetworkTables.isConnected(),
            'timestamp': time.time()
        }
    
        os.makedirs('/home/lvuser/deploy', exist_ok=True)
        with open('/home/lvuser/deploy/status.json', 'w') as f:
            json.dump(data, f, indent=2)
        
        voltage = data['batteryVoltage']
        mode = data['robotMode']
            
        time.sleep(0.05)  # 20Hz update rate
        
    except KeyboardInterrupt:
        print("\nbridge stopped")
        break
    except Exception as e:
        print(f"\n❌ Error: {e}")
        time.sleep(1)