import sys
import random
if __name__ == "__main__":
    filename = sys.argv[1]
    k = int(sys.argv[2])
    f = open(filename, 'r')

    # Read the file, each line has 6 pixels
    colors = []

    f.readline()
    info = f.readline()
    info_2 = f.readline()

    res = []

    for x in f:
        res += x.replace(" \n", "").split(" ")

    for i in range(0, len(res), 3):
        colors.append([int(res[i]), int(res[i+1]), int(res[i+2])])

    print(len(colors) % 3)
    # res = res.split()

    # Pick k random colors
    # random_colors = []
    # for i in range(k):
    #     random_colors.append(colors[random.randint(0, len(colors)-1)])

    # while True:
    #     # Assign each pixel to the closest color
    #     clusters = [[] for i in range(k)]
    #     for i in range(len(colors)):
    #         min_dist = sys.maxsize
    #         min_index = -1
    #         for j in range(k):
    #             dist = 0
    #             for l in range(3):
    #                 print(f"i = {i}, j = {j}, l = {l}")
    #                 dist += (colors[i][l] - random_colors[j][l])**2
    #             if dist < min_dist:
    #                 min_dist = dist
    #                 min_index = j
    #         clusters[min_index].append(i)

    #     # Update the centroid of each cluster
    #     for i in range(k):
    #         if len(clusters[i]) == 0:
    #             continue
    #         new_color = [0, 0, 0]
    #         for j in clusters[i]:
    #             for l in range(3):
    #                 new_color[l] += colors[j][l]
    #         for l in range(3):
    #             new_color[l] /= len(clusters[i])
    #         random_colors[i] = new_color

    #     # Check if the centroids have converged
    #     converged = True
    #     for i in range(k):
    #         for j in range(3):
    #             if abs(random_colors[i][j] - colors[clusters[i][0]][j]) > 0.001:
    #                 converged = False
    #                 break
    #         if not converged:
    #             break
    #     if converged:
    #         break

    # # Write the output
    # output = open('output.ppm', 'w')
    # output.write("P3\n")
    # output.write(info)
    # output.write(info_2)
    # # write the pixels
    # for i in range(len(colors)):
    #     output.write(str(colors[i][0]) + " " +
    #                  str(colors[i][1]) + " " + str(colors[i][2]) + " ")
    #     if (i+1) % 3 == 0:
    #         output.write("\n")
    # output.close()
