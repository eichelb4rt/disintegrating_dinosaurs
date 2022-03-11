import imageio as iio
import glob
from pathlib import Path

END_STATE_PATH = "plots/end_result.png"
ITERATION_PATHS = "plots/*_iteration_*.png"


def get_iteration(file_name):
    return int(Path(file_name).stem.split("_")[-1])


with iio.get_writer('animations/animation.gif', mode='I') as writer:
    file_names = [(get_iteration(file), file)
                  for file in glob.glob(ITERATION_PATHS)]
    file_names.sort(key=lambda tup: tup[0])
    # print(file_names)
    for iteration, file_name in file_names:
        image = iio.imread(file_name)
        writer.append_data(image)
    
    # animate the last thing a bit
    image = iio.imread(END_STATE_PATH)
    for _ in range(20):
        writer.append_data(image)
