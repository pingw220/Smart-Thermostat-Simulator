import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split

# Function to train the temperature predictor model
def train_temperature_predictor(data):
    X = data[['temperature_2m']]  # Assuming 'temperature_2m' is the column with temperature data
    y = data['temperature_2m'].shift(-1)  # Predict the next temperature reading
    X_train, X_test, y_train, y_test = train_test_split(X[:-1], y[:-1], test_size=0.2, random_state=42)
    
    model = RandomForestRegressor(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)
    return model

# Load your data
data = pd.read_csv('/Users/pingw220/Coding/ML/Smart Thermostat Simulator/data/hsinchu_temperature_data.csv')
data['time'] = pd.to_datetime(data['time'])  # Ensure 'time' is in datetime format

# Train the model using the data
model = train_temperature_predictor(data)

# Simulator class definition
class Simulator:
    def __init__(self, data, model):
        self.data = data
        self.model = model

    def run(self):
        for index, row in self.data.iterrows():
            if index < len(self.data) - 1:  # Avoid running out of data
                current_temp = pd.DataFrame({'temperature_2m': [row['temperature_2m']]})  # Ensure consistent feature names
                predicted_temp = self.model.predict(current_temp)[0]
                adjustment = self.decide_adjustment(predicted_temp)
                print(f"At {row['time']}, predicted next temp {predicted_temp}°C, adjustment made: {adjustment}")

    def decide_adjustment(self, predicted_temp):
        if predicted_temp < 20:
            return "Increase heating"
        elif predicted_temp > 25:
            return "Decrease heating"
        else:
            return "Hold temperature"

# Create an instance of the simulator and run it
simulator = Simulator(data, model)
simulator.run()

# Example of a simple test to check prediction logic
def test_predictor_accuracy(data, model):
    X_test = data[['temperature_2m']][:-1]  # Assume last value cannot be used because there's no next value to predict
    y_true = data['temperature_2m'].shift(-1).dropna()  # True next temperatures
    y_pred = model.predict(X_test)  # Model predictions
    mse = ((y_pred - y_true) ** 2).mean()  # Mean Squared Error
    print(f"Mean Squared Error of the model: {mse}")

test_predictor_accuracy(data, model)

import matplotlib.pyplot as plt

# Plot actual vs. predicted temperatures
plt.figure(figsize=(14, 7))
plt.plot(data['time'][:-1], data['temperature_2m'][:-1], label='Actual Temperatures')
plt.plot(data['time'][:-1], model.predict(data[['temperature_2m']][:-1]), label='Predicted Temperatures', linestyle='--')
plt.title('Actual vs. Predicted Temperatures')
plt.xlabel('Time')
plt.ylabel('Temperature (°C)')
plt.legend()
plt.show()