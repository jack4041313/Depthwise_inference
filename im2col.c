/*--------------------------------
im2col one channel
---------------------------------*/
static void im2col_Jack_Cheng(size_t batch_size, size_t channels, size_t in_dim, size_t out_dim,
    		   const elem_t * input,
    		   elem_t * output,
    		   const struct ConvParams * params){
    		   
    int output_start_point = 0;
    
    for(int b=0; b<batch_size; b++){
    
        for(int row=-(params->padding); row<params->in_dim - params->kernel_size + params->padding + 1; row+=(params->stride)){
            
            for(int col=-(params->padding); col<params->in_dim - params->kernel_size + params->padding + 1; col+=(params->stride)){
                
                int output_jump_index = 0;
                // scan input like kernel    
                for(int k_r=0; k_r<(params->kernel_size); k_r++){
                
                    for(int k_c=0; k_c<(params->kernel_size); k_c++){
                        
                        // printf("index = %d,", row*in_dim + col);
                        int offset = (row*in_dim + col) + ((k_r*in_dim) + k_c) ; // (start point) + (path of kernel)
                        
                        int output_array_offset = output_start_point + output_jump_index*(out_dim*out_dim);
                        //printf("address = %d,\n", output_array_offset);
                        
                        *(output + output_array_offset) = *(input + offset);
                        
              		 output_jump_index++;
                       // printf("%d ",*(input + offset));
                        
                    }  
                     //printf("\n");
                }
                output_start_point++;
            }    
            //printf("\n");
        }
    }
}

/*--------------------------------
im2col for multiple channel with no padding
---------------------------------*/
static void im2col_multi_channel(size_t batch_size, size_t cur_channels, size_t out_dim,
    		   const elem_t * input,
    		   elem_t * output,
    		   const struct ConvParams * params){
    		   
    int output_start_point = 0;
    


    for(int b=0; b<batch_size; b++){
    
        for(int row=0; row<params->in_dim - params->kernel_size + params->padding + 1; row+=(params->stride)){
            
            for(int col=cur_channels; col<(params->in_dim - params->kernel_size + 1)*(params->in_channels); col+=(params->stride)*(params->in_channels)){
                
                int output_jump_index = 0;
                
                //Debug for start point
                /*
                printf("index = %d\n", row*(params->in_dim)*(params->in_channels) + col);
                printf("row = %d\n", row);
                printf("in_dim = %d\n", (params->in_dim));
                printf("col = %d\n", col);
                */
                                    
                // scan input like kernel    
                for(int k_r=0; k_r<(params->kernel_size); k_r++){
                    
                    int kernel_size = 0;
                    
                    for(int k_c=0; kernel_size<(params->kernel_size); k_c+=(params->in_channels)){
                        
                        //Debug for path of kernel
                                                /*/*
                        printf("index = %d\n", ((k_r*(params->in_dim)*(params->in_channels)) + k_c));
                        printf("k_r = %d\n", k_r);
                        printf("in_dim = %d\n", (params->in_dim));
                        printf("k_c= %d\n", k_c);
                        */
                        
                        // (start point) + (path of kernel)
                        //int offset = (row*(params->in_dim)*(params->in_channels)*(params->stride) + col) + (((k_r*(params->in_dim)*(params->in_channels)) + k_c) ) ; 
                        int offset = (row*(params->in_dim)*(params->in_channels) + col) + (((k_r*(params->in_dim)*(params->in_channels)) + k_c) ) ; 
                        
                        int output_array_offset = output_start_point + output_jump_index*(out_dim*out_dim);
                        
                        /*
                        printf("output_array_offset = %d,\n", output_array_offset);
                        printf("offset = %d\n", offset);
                        printf("actul number = %d\n\n", *(input + offset));
                        */
                        
                        *(output + output_array_offset) = *(input + offset);
                        
              		 output_jump_index++;
              		 kernel_size++;
                       //printf("%d ",*(input + offset));
                        
                    }  
                     //printf("\n");
                }
                output_start_point++;
            }    
            //printf("\n");
        }
    }

}