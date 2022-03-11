import matplotlib.pyplot as plt
import pandas as pd
import glob
from pathlib import Path

END_STATE_PATH = "out/out.csv"
ITERATION_PATHS = "out/*_iteration_*.csv"


def get_iteration(file_name):
    return int(Path(file_name).stem.split("_")[-1])


def main():
    for file_name in glob.glob(ITERATION_PATHS):
        df = pd.read_csv(file_name, header=None)
        plt.scatter(df[0], df[1])
        plt.title(f"Iteration: {get_iteration(file_name)}")
        plt.axis('equal')
        plt.savefig(f"plots/plot_{Path(file_name).stem}.png")
        plt.clf()

    # visualize last state
    df = pd.read_csv(END_STATE_PATH, header=None)
    plt.scatter(df[0], df[1])
    plt.title(f"End Result")
    plt.axis('equal')
    plt.savefig(f"plots/end_result.png")
    plt.clf()


if __name__ == "__main__":
    main()
