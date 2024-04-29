import pandas as pd
import matplotlib.pyplot as plt

class Simulator:
    def __init__(self, data):
        self.data = data
    
    def run(self):
        # Example simulation loop
        for index, row in self.data.iterrows():
            current_temp = row['temperature_2m']  # Updated column name here
            # Perform simulation step with current_temp
            # ...

# Load the temperature data
data = pd.read_csv('/Users/pingw220/Coding/ML/Smart Thermostat Simulator/data/hsinchu_temperature_data.csv')

# Ensure only temperature data rows are loaded
data = data[['time', 'temperature_2m']].dropna()

# Convert time column to datetime
data['time'] = pd.to_datetime(data['time'])

# Create a Simulator instance with the temperature data
simulator = Simulator(data)

# Run the simulation
simulator.run()

# Depending on the specifics of your simulator, you might have additional methods
# or steps here to process the data, generate outputs, etc.

plt.figure(figsize=(10, 5))
plt.plot(data['time'], data['temperature_2m'], label='Temperature')
plt.title('Temperature Adjustments Over Time')
plt.xlabel('Time')
plt.ylabel('Temperature (°C)')
plt.legend()
plt.show()
