// #include <SDL2/SDL.h>
#pragma once

#include "cup.h"

#define CUPS_H 50
#define CUPS_W 50

class Graph
{
private:
  int _numVertices;
  vector<vector<int>> _adjList;

public:
  // numVertices = n;
  // adjList.resize(numVertices);
  void addEdgesFromPairs(int numVertices,vector<pair<int, int>> pairs)
  {
    _numVertices  = numVertices;
    _adjList.resize(numVertices);
     for (auto pair : pairs)
    {
      addEdge(pair.first, pair.second);
    }
  }

  void addEdge(int src, int dest)
  {
    _adjList[src].push_back(dest);
    _adjList[dest].push_back(src); // assuming an undirected graph
  }

    vector<int> findPathBFS(int start, int end) {
        vector<bool> visited(_numVertices, false);
        vector<int> parent(_numVertices, -1);
        queue<int> q;

        visited[start] = true;
        q.push(start);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : _adjList[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = curr;
                    q.push(neighbor);
                }
            }
        }

        if (!visited[end]) {
            return {}; // end node not found
        }

        vector<int> path;
        int curr = end;

        while (parent[curr] != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }

        return path;
    }
};

class Cups_Board
{
public:
  Cups_Board();
  ~Cups_Board();
  // init new level

  void cups_board_render_update(SDL_Renderer *);
  void handle_mouse(int x, int y);
  static SDL_Rect get_rect_point(int number_point);

private:
  void create_cups();
  void create_paths(SDL_Renderer *);
  vector<int> show_available_move(const SDL_Rect *);
  int find_number_point(int, int);
  bool check_point_free(int);
  bool check_point_repeat(vector<int>, int);
  bool _check_winning_position();

  void init_level(int lvl);
  struct Cups_board_free_paths
  {
    vector<int> available_places;
    const SDL_Color *color;
  };

  thread *thr1;
  int _level;
  int _num_cup_is_checked; // number of cup is cheked [1 ... N]
  Cup **_cups_array;
  Cup *_implicit_array; // array of available move
  SDL_Renderer *_paths;
  Cups_board_free_paths _free_paths;
  Graph graph;
};
