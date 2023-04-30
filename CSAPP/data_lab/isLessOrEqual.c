// x <= y ,return 1
// x >  y ,return 0
int isLessOrEqual(int x,int y) {
    
    int num = x + (~y+1) + (~1+1);
    int flag = num & (1 << 31);
    return !!flag;

}
