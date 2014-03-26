
template<T>
struct vertex{
    std::vector<vertex *> edges;
    std::vector<bbox> edge_bbox;
    std::list<T> contents;
}

template<T>
vertex<T> * kd_child(vertex<T> * node, FLOAT * pos){
    if (edges.length == 1) return node;
    if (in_box(edge_bbox[0])) return edges[1];
    return edges[2];
}


