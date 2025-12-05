# Navigation-System-C-
This project implements a simple command-line application in C to find the shortest path between locations on a predefined campus map using Dijkstra's Algorithm.
🚀 Features

Shortest Path Calculation: Finds the path with the minimum total distance (weight).

Step-by-Step Navigation: Provides clear, directional instructions for the route.

Undirected Graph: All paths can be traveled in both directions.

Interactive Interface: Allows the user to repeatedly query for new routes until they choose to exit.

🗺️ Campus Model (Nodes)

The system operates on a graph with 17 predefined locations:

ID                        Node Name

0                         PunchGate

1                         Joint01

2                         Joint02

3                         Joint03

4                         Joint04

5                         Ground

6                         WiFi

7                         LectureGallery

8                         MBA

9                         Class107-111

10                         Class112-115

11                         Pigeonhole

12                         PrayerHall

13                         Journal

14                         Auditorium

15                         StairsCafe

16                         Gate

🧠 How It Works (Technical Overview)

Graph Representation: The campus map is stored as an Adjacency List using C structs (Edge). Each edge stores the destination node, the distance (weight), and the direction (dir).

Algorithm: The dijkstra function is the core of the system. It uses a greedy approach to find the minimum distance from the source node to every other reachable node.

Path Reconstruction: Instead of just calculating the distance, Dijkstra's algorithm also populates a parent array. The print_route function uses this array to backtrack from the destination to the source, reconstructing the correct sequence of nodes and printing the stored directional instructions.

Error Handling: Includes checks for invalid node names and cases where no path exists.

