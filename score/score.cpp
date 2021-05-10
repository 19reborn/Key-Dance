#include<cstdio>
#include<cmath>
#include<cstring>

#define S 100
#define M 1000
#define L 10000

using namespace std;

struct block{
    double Begin;
    int col;
    double in_t;
}MY_block[10005];

double score(const char *out_file,const char *wav_file,double offset){
/*
#include<cstdio>
#include<cmath>
#include<cstring>
*/
// read files
    // read in keyboard data
    int block_num = 0;
    freopen(out_file,"r",stdin);
    while(scanf("%lf %d %lf",&MY_block[block_num].Begin,&MY_block[block_num].col,&MY_block[block_num].in_t) == 3) block_num++;
    
    fclose(stdin);

    // read in music data
    freopen(wav_file,"r",stdin);
    int length; scanf("%d",&length);
    int zf[length+3][2];
    for(int i=1;i<=length;i++){
        scanf("%d%d",&zf[i][0],&zf[i][1]);
        //zf[i][0] = abs(zf[i][0]),zf[i][1] = abs(zf[i][1]);
    }
    
    // calculate keyboard data sequence (time as x-axis)
    int aj[length+3][2];
    memset(aj,0,sizeof(aj));
    for(int i=0;i<block_num;i++)
        for(int j=(int)floor((offset+MY_block[i].Begin)*100)+1;j<=(int)ceil((offset+MY_block[i].Begin+MY_block[i].in_t)*100)+1 && j<=length;j++)
            aj[j][0] += MY_block[i].col<2,aj[j][1] += MY_block[i].col>=2;

    /*
    freopen("test.txt","w",stdout);
    for(int i=1;i<=length;i++) printf("%.2lf %d %d\n",(i-1)*0.01,aj[i][0],aj[i][1]);
    */

// get score
    double tot_score = 0;
    
    // First compute the Variance of the numbers of each type Block
    double cnt[4] = {0,0,0,0},sum,aver,var;
    for(int i=0;i<block_num;i++) cnt[MY_block[i].col]+=1;
    sum = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    cnt[0]/=sum,cnt[1]/=sum,cnt[2]/=sum,cnt[3]/=sum;
    aver = (cnt[0] + cnt[1] + cnt[2] + cnt[3])/4;
    var = ((cnt[0]-aver)*(cnt[0]-aver)+(cnt[1]-aver)*(cnt[1]-aver)+(cnt[2]-aver)*(cnt[2]-aver)+(cnt[3]-aver)*(cnt[3]-aver))/4;
    // bigger sum means more convergent，so more penalty will come...
    tot_score += S * exp(-var) / log(sum+0.5);
        //printf("%lf\n",tot_score); // test



    // Second compute the Variance of the total time of each type Block
    memset(cnt,0,sizeof(cnt)),sum=0,aver=0,var=0;
    for(int i=0;i<block_num;i++) cnt[MY_block[i].col]+=MY_block[i].in_t;
    sum = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    cnt[0]/=sum,cnt[1]/=sum,cnt[2]/=sum,cnt[3]/=sum;
    aver = (cnt[0] + cnt[1] + cnt[2] + cnt[3])/4;
    var = ((cnt[0]-aver)*(cnt[0]-aver)+(cnt[1]-aver)*(cnt[1]-aver)+(cnt[2]-aver)*(cnt[2]-aver)+(cnt[3]-aver)*(cnt[3]-aver))/4;
    // bigger sum means more convergent，so more penalty will come...
    tot_score += S * exp(-var) / log(sum * 10); // in average one block ~ 0.1 second
        // printf("%lf\n",tot_score); // test
    
    

    // compare out.txt with the wav-file   using cosine 


    // left channel
    double dot_sum = 0,length_wave = 0,length_key = 0,aver_key = 0;
    for(int i=1;i<=length;i++){
        dot_sum += aj[i][0] * zf[i][0];
        length_wave += zf[i][0] * (double)zf[i][0];
        length_key += aj[i][0] * aj[i][0];
        aver_key += aj[i][0];
    }
    dot_sum /= (sqrt(length_key) * sqrt(length_wave));
    tot_score += L * dot_sum;

    aver_key /= length;
    length_key /= length;
    tot_score += M * (length_key - aver_key*aver_key);

    // right channel

    dot_sum = 0,length_wave = 0,length_key = 0,aver_key = 0;
    for(int i=1;i<=length;i++){
        dot_sum += aj[i][1] * zf[i][1];
        length_wave += zf[i][1] * (double)zf[i][1];
        length_key += aj[i][1] * aj[i][1];
    }
    dot_sum /= ((sqrt(length_key) * sqrt(length_wave))+0.2);
    tot_score += L * dot_sum;   

    aver_key /= (length+0.1);
    length_key /= (length+0.1);
    tot_score += M * (length_key - aver_key*aver_key);

    if(tot_score<(double)0.0)
        tot_score=0.0;
    return tot_score;    
}
