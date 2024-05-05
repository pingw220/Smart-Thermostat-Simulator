# Smart Thermostat Simulator with Machine Learning

This project implements a smart thermostat simulator that utilizes machine learning to predict and adjust temperatures based on historical data. It uses a RandomForestRegressor from scikit-learn to predict the next temperature reading and makes adjustments accordingly.

## Installation

Before running this simulator, ensure you have Python and pandas installed on your system. Additionally, you'll need `scikit-learn` and `matplotlib` to run the simulations and visualize the results.

```bash
pip install pandas scikit-learn matplotlib
```

## Usage

1. Place your temperature data file in the project directory. Ensure it's named `hsinchu_temperature_data.csv` and includes 'temperature_2m' and 'time' columns.
2. Run the simulator script:

```bash
python model.py
```

This will start the simulation, printing the predicted temperatures and adjustments made at each step.

## Features

- **Data Processing**: Converts time data to datetime format for better processing.
- **Temperature Prediction**: Uses RandomForestRegressor to predict the next temperature.
- **Adjustment Decisions**: Decides whether to increase, decrease, or hold the temperature based on the prediction.

## Testing

The script includes a function `test_predictor_accuracy` to evaluate the model's performance using Mean Squared Error.

## Visualization

Generates a plot of actual vs. predicted temperatures over time, providing a visual representation of the model's performance.

## Note

This is a simulation intended for educational purposes and may require adjustments for use in actual thermostat control systems.

# Arduino Temperature Control System

This Arduino-based project controls a heating system by predicting the next temperature using a linear model and adjusting heating accordingly. It uses two LEDs to indicate whether to increase or decrease the heating.

## Demo

The link provided is the Wokwi simulation.([link](https://wokwi.com/projects/397066219278095361))

## Installation

You need the Arduino IDE installed and configured for your Arduino board. No additional libraries are required for the basic functionality.

## Setup

1. Connect two LEDs to pins 9 and 10 on your Arduino board.
2. Upload the code to your Arduino.

## Usage

Once the code is uploaded, the Arduino will:
- Predict the next temperature using the current temperature data.
- Update the linear model dynamically based on the actual next temperature.
- Turn on the appropriate LED based on the predicted temperature:
  - Red LED (pin 9) for "Increase Heating"
  - Green LED (pin 10) for "Decrease Heating"

## Features

- **Model Updating**: Continuously updates its prediction model based on new temperature data.
- **Temperature Thresholds**: Uses defined thresholds to control heating actions.

## Note

This project is designed for demonstration purposes and should be customized based on specific hardware and temperature range considerations.

## Future Improvements

- Implement connectivity to a central heating system controller.
- Add sensors for real-time temperature data acquisition.
