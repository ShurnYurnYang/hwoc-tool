import matplotlib.pyplot as plt
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
        self.dataframe.plot(x=x, y=y)
        plt.show()