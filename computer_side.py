import serial
import mysql.connector
from mysql.connector import Error

# MySQL connection configuration
db_config = {
    'user': 'root',
    'password': 'root@123',
    'host': '127.0.0.1',  # Update with your MySQL server IP address
    'database': 'inventory'
}

# Serial port configuration
serial_port = 'COM13'  # Update with the correct COM port for your Arduino
baud_rate = 9600

def insert_data(rfid, temperature, humidity, initial_weight, final_weight, inventory_weight):
    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        query = """
        INSERT INTO truck_data (rfid, temperature, humidity, initial_weight, final_weight, inventory_weight)
        VALUES (%s, %s, %s, %s, %s, %s)
        """
        cursor.execute(query, (rfid, temperature, humidity, initial_weight, final_weight, inventory_weight))
        connection.commit()
        print("Data inserted successfully")
    except Error as e:
        print(f"Error: {e}")
    finally:
        if (connection.is_connected()):
            cursor.close()
            connection.close()

def main():
    ser = serial.Serial(serial_port, baud_rate)
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line.startswith("DATA"):
                _, rfid, temperature, humidity, initial_weight, final_weight, inventory_weight = line.split(',')
                insert_data(rfid, float(temperature), float(humidity), float(initial_weight), float(final_weight), float(inventory_weight))

if __name__ == "__main__":
    main()
