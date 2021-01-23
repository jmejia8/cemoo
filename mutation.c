/* This is the module used to formulate the mutation routine*/


void realmutate(float *new_pop_ptr, int popsize, int nvar, float pmut_r, float dim, float lim_r[nvar][2])
{
  int i,j;
  float rnd,delta,indi,deltaq;
  float y,yl,yu,val,xy;
  
  for(j = 0;j < popsize;j++)
    {
      for (i = 0;i < nvar; i++)
	{
	  rnd = rand01();
	  
	  /*For each variable find whether to do mutation or not*/
	  if(rnd <= pmut_r)
	    {
	      y = new_pop_ptr[j* nvar+i];
	      yl = lim_r[i][0];
	      yu = lim_r[i][1];
	      
	      if(y > yl)
		{
		  /*Calculate delta*/
		  
		  if((y-yl) < (yu-y))
		    delta = (y - yl)/(yu - yl);
		  else
		    delta = (yu - y)/(yu-yl);
		  
		  rnd = rand01(); 
		  
		  indi = 1.0/(dim +1.0);
		  
		  if(rnd <= 0.5)
		    {
		      xy = 1.0-delta;
		      val = 2*rnd+(1-2*rnd)*(pow(xy,(dim+1)));
		      deltaq =  pow(val,indi) - 1.0;
		    }
		  else
		    {
		      xy = 1.0-delta;
		      val = 2.0*(1.0-rnd)+2.0*(rnd-0.5)*(pow(xy,(dim+1)));
		      deltaq = 1.0 - (pow(val,indi));
		    }
		  
		  /*Change the value for the parent */
		  //  *ptr  = *ptr + deltaq*(yu-yl);
		  // Added by Deb (31/10/01)
		  y = y + deltaq * (yu-yl);
		  if (y < yl) y=yl; 
		  if (y > yu) y=yu;
		  new_pop_ptr[j*nvar + i] = y;
		}
	      else // y == yl 
		{
		  xy = rand01();
		  new_pop_ptr[j*nvar + i] = xy*(yu - yl) + yl;
		}
	    }
	  //  ptr++;
	}
    }
  return ;
}
