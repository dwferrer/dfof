//simple operations on bounding boxes


struct bbox{
    FLOAT * x_l;
    FLOAT * x_h;
}

inline int box_in_box(bbox &outer,bbox &inner){
    for(int i = 0; i < VEC_SIZE; i++)
        if (outer.x_l[i] >= inner.x_l[i]) return 0;
    for(int i = 0; i < VEC_SIZE; i++)
        if (outer.x_h[i] <= inner.x_h[i]) return 0;
    return 1;
}

inline int box_intersect(bbox &a, bbox &b){
    for(int i = 0; i < VEC_SIZE; i++)
        if (a.x_h[i] < b.x_l[i]) return 0;
    for(int i = 0; i < VEC_SIZE; i++)
        if (a.x_l[i] > b.x_h[i]) return 0;
    return 1;
} 

inline int in_box(bbox &b, FLOAT *pos){
     for(int i = 0; i < VEC_SIZE; i++)
        if (pos[i] <= b.x_l) return 0;
     for(int i = 0; i < VEC_SIZE; i++)
        if (pos[i] >= b.x_h) return 0;
}
