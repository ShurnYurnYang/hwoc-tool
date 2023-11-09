import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import pandas as pd
import os


class GPUData:
    def __init__(self, filepath):
        self.filepath = os.path.join(os.getcwd(), filepath)
        self.dataframe = self.load_data()

    def load_data(self):
        return pd.read_csv(self.filepath, engine="pyarrow", skip_blank_lines=True)
    
    # takes the dataframe and generate a line plot with the given x and y axis and show the plot
    def plot(self, x, y):

        self.dataframe[x] = pd.to_datetime(self.dataframe[x])

        self.dataframe.plot(x=x, y=y)

        plt.gca().xaxis.set_major_locator(mdates.AutoDateLocator(minticks=30, maxticks=60))  # Adjusts tick density automatically
        plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d %H:%M:%S'))  # Specify date/time format
        plt.gca().set_xlim(self.dataframe[x].min(), self.dataframe[x].max())  # Set the x-axis limits

        plt.gca().yaxis.set_major_locator(plt.MaxNLocator(20))  # Adjusts tick density automatically

        #plt.gca().set_ylim(top=2000)  # Set y-axis range

        plt.xlabel("Local Time")

        plt.ylabel(y)

        plt.title(f"{y} vs Local Time")

        plt.xticks(rotation=45)

        plt.show()