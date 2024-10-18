import pandas as pd
import json
import os
import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

if __name__ == "__main__":
    # Get time for benchmark
    t1 = time.time()

    # just in case, quit the execution when more than 1 argument (namely the path) was given
    print("\nStarting visualization:")
    command_line_arguments = sys.argv
    if len(command_line_arguments) < 2 or len(command_line_arguments) > 3:
        print("No path to a preferences.json given.\nExit visualization program.")
        sys.exit()
    elif not os.path.exists(command_line_arguments[1]):
        print("Given argument is no valid file!\nExit visualization program.")
        sys.exit()

    preferences_path = command_line_arguments[1]
    with open(preferences_path) as file:
        user_preferences = json.load(file)

    # read data
    import_path = user_preferences["io"]["output_path"]

    # check import path
    if not os.path.exists(import_path):
        print("Given path leads to no valid file!\nExit visualization program.")
        sys.exit()

    # TODO: Check .csv file!
    image_df = pd.read_csv(import_path, names=["x", "y", "frame"])
    frame_num = image_df["frame"].nunique()
    fig = plt.figure()
    images = []

    # start generating animation
    for i in range(frame_num):
        print("Generating frame {}/{}".format(i + 1, frame_num))
        frame_group_df = image_df.loc[image_df['frame'] == i+1]
        x_coordinates = frame_group_df["x"]
        y_coordinates = frame_group_df["y"]
        plt.xlim([0, 100])
        plt.ylim([0, 100])
        image = plt.scatter(x_coordinates, y_coordinates, c="blue")
        images.append([image])

    print("Concatenating frames...")
    animation = animation.ArtistAnimation(fig, images, interval=1, blit=True, repeat_delay=20)

    # save animation
    animation.save(user_preferences["io"]["animation_path"])

    print("Done!")

    # print runtime for benchmark
    time = round(time.time() - t1, 2)
    print("Runtime for visualization: {} seconds".format(time))