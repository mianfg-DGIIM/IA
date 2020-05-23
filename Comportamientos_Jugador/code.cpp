struct Graph {
    std::unordered_map<char, std::vector<char> > edges;

    std::vector<char> neighbors(char id) {
        return edges[id];
    }
}

void breadth_first_search(SimpleGraph graph, char start) {
    std::queue<char> frontier;
    frontier.push(start);

    std::unordered_set<char> visited;
    visited.insert(start);

    while (!frontier.empty()) {
        char current = frontier.front();
        frontier.pop();

        std::cout << "Visiting " << current << '\n';
        for (char next : graph.neighbors(current)) {
            if (visited.find(next) == visited.end()) {
                frontier.push(next);
                visited.insert(next);
            }
        }
    }
}

int main() {
    breadth_first_search(example_graph, 'A');
}

struct GridLocation {
    int x, y;
}

namespace std {
    template <> struct hash<GridLocation> {
        typedef GridLocation argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const GridLocation &id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

struct SquareGrid {
    static std::array<GridLocation, 4> DIRS;

    int width, height;
    std::unordered_set<GridLocation> walls;

    SquareGrid(int width_, int height_)
        : width(width_), height(height_) {}
    
    bool in_bounds(GridLocation id) const {
        return 0 <= id.x && id.x < width
            && 0 <= id.y && id.y < height;
    }

    bool passable(GridLocation id) const {
        return walls.find(id) == walls.end();
    }

    std::vector<GridLocation> neighbors(GridLocation id) const {
        std::vector<GridLocation> results;

        for (GridLocation dir : DIRS) {
            GridLocation next{id.x + dir.x, id.y + dir.y};
            if (in_bounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        if ((id.x + id.y) % 2 == 0) {
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};

std::array<GridLocation, 4> SquareGrid::DIRS =
    {GridLocation{1,0}, GridLocation{0,-1}, GridLocation{-1,0}, GridLocation{0,1}};


// BFS
template<typename Location, typename Graph>
std::unordered_map<Location, Location>
breadth_first_search(Graph graph, Location start) {
    std::queue<Location> frontier;
    frontier.push(start);

    std::unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        Location current = frontier.front();
        frontier.pop();

        for (Location next : graph.neighbors(current)) {
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }
    return came_from;
}

// BFS with goal
template<typename Location, typename Graph>
std::unordered_map<Location, Location>
breadth_first_search(Graph graph, Location start, Location goal) {
    std::queue<Location> frontier;
    frontier.push(start);

    std::unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        Location current = frontier.front();
        frontier.pop();

        if (current == goal) break;

        for ( Location next : graph.neighbors(current) ) {
            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }

    return came_from;
}