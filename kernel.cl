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

__kernel void gen_circle(__global float* data){
    const int i = get_global_id(0);
    const int size = get_global_size(0);
    const int cloc = i % 6;
    const int vloc = i / 6.0f;
    const int vloct = (int)(i / 6.0f) % 3;
  
    const float acc = 50.0f;
    const float th = 360.0f/acc;
    const float cx = 2.0f;
    const float cy = 2.0f;
    const float cz = 2.0f;
    const float r =  2.0f;

     //texture thread
    if(cloc == 3 || cloc == 4){
        data[i] = 0.f;
    }
    else if(cloc == 5){
        data[i] = 1.0f;
    }

    else if(cloc == 0){
       //x
       if(vloct == 0){
            data[i] = xngonxy(cx, cy, cz, cx + r, cy, cz, th, (float)vloc);
       }
       else if(vloct == 1){
            data[i] = xngonxy(cx, cy, cz, cx + r, cy, cz, th, (float)vloc + 1);
       }

       else{
           data[i] = cx;
       }
    }

    else if(cloc == 1){
       //y
       if(vloct == 0){
            data[i] = yngonxy(cx, cy, cz, cx + r, cy, cz, th, (float)vloc);
       }
       else if(vloct == 1){
            data[i] = yngonxy(cx, cy, cz, cx + r, cy, cz, th, (float)vloc + 1);
       }

       else{
           data[i] = cy;
       }
    }

    else if(cloc == 2){
        //z
        data[i] = cz;
    }
   
};