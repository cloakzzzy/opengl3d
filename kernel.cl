/*
    0 : x
    1 : y
    2 : z

    3 : tx
    4 : ty
    
    5 : type (3d if 1.0f)
*/

float xngonxy(float cx, float cy, float cz, float spx, float spy, float spz, float deg, float itr) {
	return(((spx - cx) * cos(radians(deg * itr)) - sin(radians(deg * itr)) * (spy - cy)) + cx);	
}

float yngonxy(float cx, float cy, float cz, float spx, float spy, float spz, float deg, float itr) {
	return(((spy - cy) * cos(radians(deg * itr)) + sin(radians(deg * itr)) * (spx - cx)) + cy);
}

__kernel void gen_circle(__global float* data, float th,  float cx,  float cy,  float cz, float r){
    const int i = get_global_id(0);
    const int size = get_global_size(0);
    const int cloc = i % 6;
    const int vloc = i / 6.0f;
    const int vloct = (int)(i / 6.0f) % 3;
    const int tloc = i / 18.0f;
 
    //texture thread
    if(cloc == 3 || cloc == 4){ data[i] = 0.f; }
    else if(cloc == 5){ data[i] = 1.0f; }

    //x
    else if(cloc == 0){
       if(vloct == 0){ data[i] = xngonxy(cx, cy, cz, cx, cy + r, cz, th, (float)tloc); }
       else if(vloct == 1){ data[i] = xngonxy(cx, cy, cz, cx, cy + r, cz, th, (float)tloc + 1);}
       else{ data[i] = cx;}
    }

    //y
    else if(cloc == 1){
       if(vloct == 0){ data[i] = yngonxy(cx, cy, cz, cx, cy + r, cz, th, (float)tloc);}
       else if(vloct == 1){ data[i] = yngonxy(cx, cy, cz, cx, cy + r, cz, th, (float)tloc + 1);}
       else{ data[i] = cy;}
    }

    //z
    else if(cloc == 2){ data[i] = cz;}
   
};