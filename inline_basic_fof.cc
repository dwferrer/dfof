long long int N = Nx[0];

for(int i = 0; i < N; i++){{
    //printf("Current id: %d\n",current_id);
    int search_idx = GROUP_END1(current_id-1);
    GID1(i) = current_id;
    int friends = 0;
    int swap_idx = search_idx;
    for(int j = search_idx; j < N; j++){{
        {FLOAT} r = 0;
        for(int d = 0; d < {VEC_SIZE}; d++) r+= (X2(i,d) - X2(j,d))*(X2(i,d) - X2(j,d)); 
        r = sqrt(r);
        {FLOAT} temp[{VEC_SIZE}];
        if (r < l){{
            friends++;
            
            //swap positions
            memcpy(&temp,&(X2(j,0)),{VEC_SIZE} *sizeof({FLOAT}));
            memcpy(&(X2(j,0)),&(X2(swap_idx,0)),{VEC_SIZE} *sizeof({FLOAT}));
            memcpy(&(X2(swap_idx,0)),&temp,{VEC_SIZE} *sizeof({FLOAT}));
            //swap number of friends
            int temp_nf = N_FRIENDS1(j) + 1; //We need to include the particle that befriended us
            N_FRIENDS1(j) = N_FRIENDS1(swap_idx);
            N_FRIENDS1(swap_idx) = temp_nf;
            swap_idx++;
        }}
        N_FRIENDS1(i) += friends;
    }}
    if(friends == 0){{
        if (i >= search_idx-1){{
            GROUP_END1(current_id) = search_idx+1;
            current_id+=1;
        }}
    }}
    else GROUP_END1(current_id-1)+=friends;
}}

return_val = current_id;



