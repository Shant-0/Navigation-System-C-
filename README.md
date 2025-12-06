# 📍Campus Navigation System

A terminal-based indoor navigation tool using Dijkstra’s Algorithm

This project implements a complete campus navigation system written in C, using:

Weighted adjacency list (linked list) graph

Dijkstra shortest-path algorithm

Compass directions (North, South-West, etc.)

Menu-driven interface

Case-insensitive and space-insensitive input

Closest amenities (Top 3) query

Perfect for navigating floors or buildings inside a campus.

# 🚀 Features

**✔ Navigate Between Locations**

Find the shortest path between any two nodes with step-by-step directions:

→ From Ground    |    go West     |    to WiFi      |    (20)

→ From WiFi      |    go North     |   to Joint03    |   (45)

→ From Joint03    |   go West     |    to MBA       |    (15)


Includes:

Exact distances

Direction words

Cleanly formatted output

**✔ Closest Amenities (Top 3)**

Example:

Top 3 closest locations to Joint04:

  • PrayerHall         → 15 units  (East)
  
  • Pigeonhole         → 20 units  (West)
  
  • Ground             → 40 units  (North-East)

**✔ Known Nodes List**

Displays all campus nodes in original order.

**✔ Input Friendly**

Not case-sensitive

Ignores spaces (class 107 111 = Class107-111)

Error-handling with automatic re-prompting.

# 🧠 How It Works (Technical Overview)

**Graph Representation:** The campus map is stored as an Adjacency List using C structs (Edge). Each edge stores the destination node, the distance (weight), and the direction (dir).

**Algorithm:** The dijkstra function is the core of the system. It uses a greedy approach to find the minimum distance from the source node to every other reachable node.

**Path Reconstruction:** Instead of just calculating the distance, Dijkstra's algorithm also populates a parent array. The print_route function uses this array to backtrack from the destination to the source, reconstructing the correct sequence of nodes and printing the stored directional instructions.

**Error Handling:** Includes checks for invalid node names and cases where no path exists.

# 📘 License

**Free to use, modify, and extend for academic or personal projects.**
