# Dijkstra algorithm 
A program that implements the Dijkstra algorithm on an arbitrary graph,
represented as a adjacency matrix or adjacency list.
1. Input data:
      
        An input file with a description of the graph. The input file should have the following form:
    ``` 
    n
    type
    vertex_1: (vertex, weight) -> (vertex, weight)...
    vertex_2: (vertex, weight) -> (vertex, weight)...
    ...
    vertex_n: (vertex, weight) -> (vertex, weight)...
    ```
    Here n is the number of vertices of the graph, type is the type of graph 
    representation in the memory (matrix/list), vertex_n is a vertex, vertex is the 
    adjacent vertex, weight is the path length between the vertices
2. User-defined parameters:
    * --start_vertex - vertex from which the shortest path should be found.
    * --end_vertex - the vertex to which you need to find the shortest path.
3. Basic requirements:
    * Dijkstra's algorithm must work regardless of how the graph is represented in 
    memory.
    * The program must output both the length of the shortest path and the path itself.
