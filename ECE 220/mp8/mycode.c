int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
  int flag = 0;
  int rowN = (*cur_game).rows;
  int colN = (*cur_game).cols;
  int i, j;
  for (j = 0; j < rowN; j++){
    for (i = colN - 1; i >= 0; i--){
      if( cur_game->cells[j*colN+i] != -1){
          int k;
          for(k = colN - 1; k > i; k--){
              if(cur_game->cells[j*colN+k] == -1) break;
          }
          if(k > i){
              cur_game->cells[j*colN+k] = cur_game->cells[j*colN+i];
              cur_game->cells[j*colN+i] = -1;
              flag = 1;
	}
      }

    }
  }

  for (j = 0; j < rowN; j++){
    for (i = colN-2; i >= 0; i--){
      if(cur_game->cells[j*colN+i] != -1){

          if(cur_game->cells[j*colN+i] == cur_game->cells[j*colN+i+1]){
              cur_game->cells[j*colN+i+1] = 2 * cur_game->cells[j*colN+i+1];
              (*cur_game).score += cur_game->cells[j*colN+i+1];
              flag = 1;
              int l;
              for (l = i; l >= 0; l--){
                  if (l != 0)
                      cur_game->cells[j*colN+l] = cur_game->cells[j*colN+l-1];
                  else cur_game->cells[j*colN+l] = -1;
              }
          }
        }
    }
  }
    //YOUR CODE STARTS HERE
    if(flag == 0)return 0;
    return 1;
};
