//
//  main.c
//  Tweet
//
//  Created by Jeong Hyun Lee on 2016. 6. 22..
//  Copyright © 2016년 Jeong Hyun Lee. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define NELEM 10000


#define WHITE 0
#define GRAY  1
#define BLACK 2



typedef struct Adj {
    int n;
    int weight;
    struct Adj* next;
} Adj;

void Adj_init(Adj* self) {
    self->n = 0;
    self->weight=0;
    self->next = NULL;
}

typedef struct Adj1 {
    int n;
    struct Adj1* next;
} Adj1;

void Adj1_init(Adj1* self) {
    self->n = 0;
    self->next = NULL;
}

typedef struct {
    char id[50];
} User;



typedef struct {
    int n;
    //char written_date[100];
    char write[50];
   // User user[100];
    int num_of_user;
    //int id[7000];
    Adj1* fir;
} Word;



typedef struct {
    char id[50];
    //char sign_up_date[50];
    //char screen_name[20];
    int n;
    int tweet_number;
    //Written write[10];
    int color;
    int parent;
    int d;
    int f;
    int fin;
    //char name[10];
    //int word[210];
    Adj* first;
    Adj1* fir;
} Vertex;

void Vertex_init(Vertex* self) {
    strcpy(self->id, "(none)");
    //strcpy(self->sign_up_date, "(none)");
    //strcpy(self->screen_name, "(none)");
    self->color = 0;
    self->parent = -1;
    self->d = 1;
    self->f = 1;
    self->fin = 1;

    //strcpy(self->name, "(none)");
    self->n = 0;
    self->first = NULL;
    self->tweet_number = 0;
}

void Word_init(Word* self) {
    //strcpy(self->user, "(none)");
    strcpy(self->write, "(none)");
    self->fir = NULL;

    //strcpy(self->written_date, "(none)");
    self->n = 0;
    self->num_of_user = 0;
}



void Vertex_add(Vertex* self, Vertex* v) {
    Adj* a = (Adj *)malloc(sizeof(Adj));
    /*
    int tmp=0;
    //printf("%slength:%d\n", v->id, (int)strlen(v->id));

    for(int i = 0; i<(int)strlen(v->id)-1; i++){
        int t=1;
        for(int j=0; j<(int)strlen(v->id)-2-i;j++)
            t*=10;
        tmp += t*((int)(v->id[i])-48);
    }
    printf("v->id:%stmp:%d\n\n", v->id, tmp);
    */
    a->n = v->n;
    a->next = self->first;
    self->first = a;
}

void Word_add(Word* self, Vertex* v) {
    Adj1* a = (Adj1 *)malloc(sizeof(Adj1));
    a->n = v->n;
    a->next = self->fir;
    self->fir = a;
}

void print_vertex(Vertex* vertices, int n) {
    printf("%d\n",vertices[n].n);
    printf("%s", vertices[n].id);
    //printf("%s", vertices[n].sign_up_date);
    //printf("%s:", vertices[n].screen_name);
    for(Adj* p = vertices[n].first; p; p = p->next) {
        printf("%s", vertices[p->n].id);
    }
    printf("\n");
}

void print_word(Vertex* vertices, int n, Word* words) {
    printf("%d\n",words[n].n);
    printf("%d\n", words[n].num_of_user);
    //printf("%s->\n", words[n].written_date);
    printf("%s", words[n].write);
    //Adj1* p = vertices[n].fir->next;
    for(Adj1* p = words[n].fir; p; p = p->next) {
        printf("%s", vertices[p->n].id);
    }
    printf("\n\n\n");
}

int number_friend(Vertex* vertices, int n){
    int cnt=0;
    for(Adj* p = vertices[n].first; p; p = p->next) {
        printf("%s", vertices[p->n].id);
        cnt++;
    }
    return cnt;
}

void friend_stat(Vertex* vertices, int total){
    int min=1000000;
    int max=0;
    int sum=0;
    for (int i = 0; i < total; i++) {
        int cnt=0;
        for(Adj* p = vertices[i].first; p; p = p->next) {
            //printf("%s", vertices[p->n].id);
            cnt++;
        }
        //printf("%d\n",cnt);
        if(min>cnt)
            min=cnt;
        if(max<cnt)
            max=cnt;
        sum+=cnt;
    }
    sum/=total;
    printf("Average number of friends : %d\nMinimum friends : %d\nMaximum number of friends : %d\n", sum, min,max);
    
    
}

void tweet_stat(Vertex* vertices, int total){
    int min=1000000;
    int max=0;
    int sum=0;
    for (int i = 0; i < total; i++) {
        int cnt = vertices[i].tweet_number;
        if(min>cnt)
            min=cnt;
        if(max<cnt)
            max=cnt;
        sum+=cnt;
    }
    sum/=total;
    printf("Average tweets per user : %d\nMinimum tweets per user : %d\nMaximum tweets per user : %d\n", sum, min,max);
}

void most_tweeted_word(Word* words, int number_of_words){
    int max=0;
    int max_user[5];
    char max_word[50];
    max_user[0]=-1;
    max_user[1]=-1;
    max_user[2]=-1;
    max_user[3]=-1;
    max_user[4]=-1;
    for(int i=0; i<5; i++){
        for(int j=0; j<number_of_words;j++){
            if(max<words[j].num_of_user && words[j].n !=max_user[0]&& words[j].n !=max_user[1]&& words[j].n !=max_user[2]&& words[j].n !=max_user[3]&& words[j].n !=max_user[4]){
                max=words[j].num_of_user;
                max_user[i]=words[j].n;
                strcpy(max_word, words[j].write);
            }
        }
        printf("Top %d most tweeted word : (%d)%s",i+1,max,max_word);
        max=0;
    }
}

void most_tweeted_user(Vertex* vertices, int total){
    int max=0;
    int max_user[5];
    char max_word[50];
    max_user[0]=-1;
    max_user[1]=-1;
    max_user[2]=-1;
    max_user[3]=-1;
    max_user[4]=-1;
    for(int i=0; i<5; i++){
        for(int j=0; j<total;j++){
            if(max<vertices[j].tweet_number && vertices[j].n !=max_user[0]&& vertices[j].n !=max_user[1]&& vertices[j].n !=max_user[2]&& vertices[j].n !=max_user[3]&& vertices[j].n !=max_user[4]){
                max=vertices[j].tweet_number;
                max_user[i]=vertices[j].n;
                strcpy(max_word, vertices[j].id);
            }
        }
        printf("Top %d most tweeted user : (%d)%s",i+1,max,max_word);
        max=0;
    }
}

void find_users_who_tweeted(Vertex* vertices, int n, Word* words, char* in){
    char tmp[50];
    //in[strlen(in)]= "\n";
    //printf("%s",in);
    for(int i=0;i<n;i++){
        int len =(int)(strlen(words[i].write))-1;
        strncpy(tmp, words[i].write, strlen(words[i].write)-1);
        //printf("%d %s",i, words[i].write);
        if(strncmp(tmp,in,len)==0 && (int)(strlen(in))==len){
            for(Adj1* p = words[i].fir; p; p = p->next) {
                printf("%s", vertices[p->n].id);
            }
            return;
        }
    }
    /*
    strcpy(tmp, "(none)");
    strncpy(tmp, words[27].write, strlen(words[27].write)-1);
    
    printf("word_write : %sin : %s",words[27].write,in);
    printf("tmp : %sin : %s",tmp,in);

    printf("\nresult : %d\n", strcmp(words[27].write,in));
     */
    printf("find_users_who_tweeted->Error!\n\n");
}

void find_users_who_tweeted_friends(Vertex* vertices, int n, Word* words, char* in){
    char tmp[50];
    //in[strlen(in)]= "\n";
   //printf("%s",in);
    for(int i=0;i<n;i++){
        int len =(int)(strlen(words[i].write))-1;
        strncpy(tmp, words[i].write, strlen(words[i].write)-1);
        //printf("%d %s",i, words[i].write);
        if(strncmp(tmp,in,len)==0 && (int)(strlen(in))==len){
            for(Adj1* p = words[i].fir; p; p = p->next) {
                printf("%s's Friends ->\n", vertices[p->n].id);
                for(Adj* pp = vertices[p->n].first; pp; pp = pp->next) {
                    printf("%s", vertices[pp->n].id);
                }
                printf("\n");
            }
            return;
        }
    }
    /*
     strcpy(tmp, "(none)");
     strncpy(tmp, words[27].write, strlen(words[27].write)-1);
     
     printf("word_write : %sin : %s",words[27].write,in);
     printf("tmp : %sin : %s",tmp,in);
     
     printf("\nresult : %d\n", strcmp(words[27].write,in));
     */
    printf("find_users_who_tweeted->Error!\n\n");
}
void delete_mentions(int n, Word* words, char* in){
    
    char tmp[50];
    //in[strlen(in)]= "\n";
    //printf("%s",in);
    for(int i=0;i<n;i++){
        int len =(int)(strlen(words[i].write))-1;
        strncpy(tmp, words[i].write, strlen(words[i].write)-1);
        //printf("%d %s",i, words[i].write);
        if(strncmp(tmp,in,len)==0 && (int)(strlen(in))==len){
            words[i].fir= NULL;
            words[i].num_of_user=0;
            return;
        }
    }
    
}
void delete_user_mentions_words(Vertex* vertices,int n, Word* words, char* in, int vertices_total){
    char tmp[50];
    //in[strlen(in)]= "\n";
    //printf("%s",in);
    int save=0;
    int i;
    for(i=0;i<n;i++){
        int len =(int)(strlen(words[i].write))-1;
        strncpy(tmp, words[i].write, strlen(words[i].write)-1);
        if(strncmp(tmp,in,len)==0 && (int)(strlen(in))==len){
            save= words[i].n;
            for(Adj1* p = words[i].fir; p; p = p->next) {
                //printf("%s", vertices[p->n].id);
                for(int j=0; j<vertices_total;j++){
                    Adj* temp;
                    int first=0;
                    for(Adj* pp = vertices[j].first; pp; pp = pp->next) {
                        if(vertices[p->n].id == vertices[pp->n].id){
                            if(first==0){
                                vertices[j].first = pp->next;
                            }
                            else
                                temp->next = pp->next;
                        }
                        temp=pp;
                        first=1;
                        //printf("%s", vertices[pp->n].id);
                    }
                    
                }
                strcpy(vertices[p->n].id,  "");
            }
            break;
        }
    }
}

int dfs_time = 0;


void dfs_visit(Vertex* vertices, int nelem, int u) {
    dfs_time++;
    vertices[u].d = dfs_time;
    vertices[u].color = GRAY;
    for (Adj* v = vertices[u].first; v; v = v->next) {
        if (vertices[v->n].color == WHITE) {
            vertices[v->n].parent = u;
            dfs_visit(vertices, nelem, v->n);
        }
    }
    vertices[u].color = BLACK;
    dfs_time++;
    vertices[u].f = dfs_time;
}

void dfs(Vertex* vertices, int nelem) {
    for(int u = 0; u < nelem; u++) {
        vertices[u].color = WHITE;
        vertices[u].parent = -1;
    }
    dfs_time = 0;
    for(int u = 0; u < nelem; u++) {
        if (vertices[u].color == WHITE) {
            dfs_visit(vertices, nelem, u);
        }
    }
}

int count_recurse=0;
int component_count=0;
int cnt_com=0;
int reverse_dfs_visit(Vertex* trans_vertices, int nelem, int u, int genesis, int* components) {
    int sort[10000];
    int count=0;
    int a=u;
    //printf("re");
    if(count_recurse>65)
        return 0;
    //printf("\n%d ",a);
    for (Adj* v = trans_vertices[u].first; v; v = v->next) {
        if(v->n==genesis)
            return 1;
        
        sort[count++] = v->n;
        
        
        /*
        int a=0;
        if(vertices[v->n].fin!=1)
            a = reverse_dfs_visit(vertices, nelem, v->n, genesis);
        if(a==1){
            vertices[v->n].fin=1;
            printf("%s",vertices[u].id);
            return 1;
        }
         */
    }
    for(int i=0; i<count;i++){
        for(int j=i; j<count;j++){
            if(trans_vertices[sort[i]].f < trans_vertices[sort[j]].f){
                int temp=sort[i];
                sort[i] = sort[j];
                sort[j]=temp;
                
            }
        }
    }
    for(int i=0; i<count; i++){
        int a=0;
        if(trans_vertices[sort[i]].fin!=1){
            count_recurse++;
            a = reverse_dfs_visit(trans_vertices, nelem, sort[i], genesis, components);
            if(a==1){
                trans_vertices[sort[i]].fin=1;
                printf("%s", trans_vertices[sort[i]].id);
                int t=0;
                for(int b=0; b<cnt_com;b++){
                    if(components[b]==sort[i])
                        t=1;
                }
                if(t==0)
                    components[cnt_com++]=sort[i];
                return 1;
            }
        }
    }
    return 0;
}


void reverse_dfs(Vertex* trans_vertices, int total_number){
    for(int u = 0; u < total_number; u++) {
        trans_vertices[u].fin = 0;
    }
    while(1){
        int turn=0;
        int max=-1;
        for(int i=0; i<total_number;i++){
            if(trans_vertices[i].f>max &&trans_vertices[i].fin !=1){
                //printf("%d ", i);
                turn=i;
                max = trans_vertices[i].f;
            }
        }
        if(max !=-1){
            trans_vertices[turn].fin=1;
            //printf("%d %d\n", total_number, component_count);
            //printf("\nComponent : \n");
            //printf("%d -> %s",turn, trans_vertices[turn].id);
            //component_count++;
            count_recurse=0;
            int components[10000];
            components[0]=turn;
            cnt_com=1;
            int a=reverse_dfs_visit(trans_vertices, total_number, turn, turn, components);
            component_count+= cnt_com;
            if(cnt_com!=1){
                printf("\n\n!!!strongly connected component!!!\n");
                for(int b=0; b<cnt_com; b++)
                    printf("%s", trans_vertices[components[b]].id);
            }
            
        }
        if(max==-1)
            return;
    }
    
    
}




void transpose(Vertex* trans_vertices,Vertex* vertices, int total_num){
    for(int i=0; i<total_num;i++){
        strcpy(trans_vertices[i].id, vertices[i].id);
        trans_vertices[i].n = vertices[i].n;
        trans_vertices[i].tweet_number = vertices[i].tweet_number;
        trans_vertices[i].d = vertices[i].d;
        trans_vertices[i].f = vertices[i].f;
        trans_vertices[i].parent = vertices[i].parent;
        trans_vertices[i].color = vertices[i].color;
    }
    for(int i=0; i<total_num;i++){
        for(Adj* p = vertices[i].first; p; p = p->next) {
            Vertex_add(&trans_vertices[p->n], &trans_vertices[i]);
        }
    }
}

void giving_weight(Vertex* vertices,int total_number){
    for(int i=0; i<total_number; i++){
        for(Adj* p = vertices[i].first; p; p = p->next) {
            int n=0;
            for(Adj* pp = vertices[p->n].first; pp; pp = pp->next) {
                n++;
            }
            p->weight =n;
        }
    }
}

void find_shortest_path(Vertex* vertices,int total_number,char* input){
    for(int u = 0; u < total_number; u++) {
        vertices[u].color = WHITE;
        vertices[u].parent = -1;
        vertices[u].d = 10000;
    }
    int start;
    for(int u = 0; u < total_number; u++) {
        char tmp[50];
        int len =(int)(strlen(vertices[u].id))-1;
        strncpy(tmp, vertices[u].id, len);
        //printf("%d %s",i, words[i].write);
        if(strncmp(tmp,input,len)==0 && (int)(strlen(input))==len){
            start=u;
            break;
        }
        
        /*
        if(strcmp(vertices[u].id,input)==0){
            start=u;
            break;
        }
         */
    }
    vertices[start].color = GRAY;
    vertices[start].d = 0;
    int min_pos;
    min_pos=start;
    while(1){
    for(int u = 0; u < total_number; u++) {
        if(vertices[u].color == GRAY){
            for(Adj* p = vertices[u].first; p; p = p->next) {
                if(vertices[p->n].color==WHITE && vertices[p->n].d > vertices[u].d + (p->weight)){
                    vertices[p->n].d = vertices[u].d + (p->weight);
                }
            }
        }
    }
    vertices[min_pos].color=BLACK;
        printf("%d %s",vertices[min_pos].d, vertices[min_pos].id );
    int min = 100000;
    min_pos=-10;
    for(int u = 0; u < total_number; u++) {
        if (min>vertices[u].d && vertices[u].color==WHITE) {
            min = vertices[u].d;
            min_pos = u;
        }
    }
    if(min_pos==-10)
        break;
    vertices[min_pos].color=GRAY;
        
    }
}







int main(int argc, const char * argv[]) {
    Vertex vertices[10000];
    Word words[50000];
    
    for(int i = 0; i < 10000; i++) {
        Vertex_init(&vertices[i]);
    }
    for(int i = 0; i < 50000; i++) {
        Word_init(&words[i]);
    }
    
    
    printf("----Total users----\n");
    FILE *fp = fopen( "user.txt", "r" );
    char arr[50];
    char *in;
    int count =0;
    while(1){
        in = fgets( arr, 50, fp );
        if( in == 0 ){
            //printf("END!!\n\n");
            break;
        }
        if(count%4==0){
            strcpy(vertices[count/4].id, arr);
        }
        else if(count%4==3){
            vertices[count/4].n=count/4;
        }
        count++;
        printf("%s",arr);
    }
    fclose(fp);
    int total_number = count/4;
    
    
    //test!!
    /*
    for(int i=0; i<count; i++){
        if(i%4==0){
            printf("%s",vertices[i/4].id);
        }
        else if(i%4==1){
            printf("%s",vertices[i/4].sign_up_date);
        }
        else if(i%4==2){
            printf("%s\n",vertices[i/4].screen_name);
        }
    }
    */
    
    
    printf("----Total friendship records----\n");
    fp = fopen( "friend.txt", "r" );
    count=0;
    char tmp[50];
    while(1){
        in = fgets( arr, 50, fp );
        if( in == 0 ){
            //printf("END!!\n\n");
            break;
        }
        if(count%3==0)
            strcpy(tmp, arr);
        else if(count%3==1){
            int a=0;
            int b=0;
            while(strcmp(vertices[a].id, tmp))
                a++;
            while(strcmp(vertices[b].id, arr))
                b++;
            int turn=0;
            for(Adj* p = vertices[a].first; p; p = p->next) {
                if(strcmp(vertices[b].id, vertices[p->n].id)==0)
                    turn=1;
            }
            if(turn==0)
                Vertex_add(&vertices[a], &vertices[b]);
        }
        printf( "%s", arr );
        count++;
    }
    fclose(fp);
    
    
    
    printf("----Total tweets----\n");
    fp = fopen( "word.txt", "r" );
    count=0;
    char tmp1[50];
    int number_of_words=0;
    while(1){
        in = fgets( arr, 50, fp );
        if( in == 0 ){
            //printf("END!!\n\n");
            break;
        }
        //printf( "count: %d(%d) -> %s",count, (int)strlen(arr),arr );

        if(count%4!=3 || strlen(arr)==1){
        if(count%4==0){
            strcpy(tmp, arr);
        }
        else if(count%4==1){
            strcpy(tmp1, arr);
        }
        else if(count%4==2){
            
            int turn=0;
            int tmp_for_word=-1;
            for(int i=0; i<number_of_words;i++){
                if(strcmp(words[i].write, arr)==0){
                    //strcpy(words[i].user[words[i].num_of_user].id,tmp);
                    words[i].num_of_user++;
                    //printf("\n%s number_of_user : %d\n",words[i].write,words[i].num_of_user);
                    tmp_for_word=i;
                    turn=1;
                    break;
                }
            }
            if(turn==0){
                strcpy(words[number_of_words].write, arr);
                words[number_of_words].n=number_of_words;
                //strcpy(words[number_of_words].user[words[number_of_words].num_of_user].id,tmp);
                words[number_of_words].num_of_user++;
                //printf("%d %d",number_of_words, num)
                //printf("\n%s number_of_user : %d\n",words[number_of_words].write,words[number_of_words].num_of_user);

                number_of_words++;
                //printf("number of words : %d\n",number_of_words);
            }
            
            
            for(int j=0; j<total_number;j++){
                if(strcmp(vertices[j].id,tmp)==0){
                    vertices[j].tweet_number++;
                    //printf("tweet number : %d\n", vertices[j].tweet_number);
                    if(turn==1)
                        Word_add(&words[tmp_for_word], &vertices[j]);
                    else
                        Word_add(&words[number_of_words-1], &vertices[j]);
                    break;
                }
            }
        }
            printf("%s",arr);
        count++;
        }
    }
    fclose(fp);
    printf("Total Number of Tweeted Words : %d\n",count/4);
    
    
    /*
    printf("Print Vertices!!\n");
    for (int i = 0; i < total_number; i++) {
        print_vertex(vertices,i);
    }
    printf("Print Words!!\n");
     for (int i = 0; i < number_of_words; i++) {
         print_word(vertices,i,words);
     }
    */
    
    char input[50];
    while(1){
    int select;
    printf("1. DISPLAY STATISTICS\n2. TOP 5 MOST TWEETED WORDS\n3. TOP 5 MOST TWEETED USERS\n4. FIND USERS WHO MENTIONED A WORD\n5. FIND ALL PEOPLE WHO ARE FRIENDS OF THE ABOVE USERS\n6. DELETE ALL MENTIONS OF A WORD\n7. DELETE ALL USERS WHO MENTIONED A WORD\n8. FIND STRONGLY CONNECTED COMPONENTS\n9. FIND SHORTEST PATH FROM A GIVEN USER\n99. QUIT\nWhich one? : ");
    scanf("%d",&select);

    if(select==1){
    //number of friends
    printf("\n\nTotal Number of Users : %d\n", total_number);
    printf("----DISPLAY STATISTICS----\n");
    friend_stat(vertices, total_number);
    
    //tweets
    tweet_stat(vertices, total_number);
        printf("\n\n");

    }
    else if(select==2){

    printf("\n\n");
    printf("----TOP 5 MOST TWEETED WORDS----\n");
    most_tweeted_word(words, number_of_words);
        printf("\n\n");

    }
    else if(select==3){

    printf("\n\n");
    printf("----TOP 5 MOST TWEETED USERS----\n");
    most_tweeted_user(vertices, total_number);
        printf("\n\n");

    }
    
    else if(select==4 ||select==5){

    
    char input1[50];
    while(strcmp(input1,"n")!=0){
        printf("\n\n----FIND USERS WHO MENTIONED A WORD----\n");
        printf("Write Tweet Word : ");
        scanf("%s",input);
        //printf("%s",input);
        find_users_who_tweeted(vertices,number_of_words,words,input);
        printf("\n\n----FIND ALL PEOPLE WHO ARE FRIENDS OF THE ABOVE USERS----\n");
        find_users_who_tweeted_friends(vertices,number_of_words,words,input);
        printf("Again?(y/n) : ");
        scanf("%s",input1);
    }
        printf("\n\n");

        }else if(select==6){

    char input2[50];
    while(strcmp(input2,"n")!=0){
        printf("\n\n----DELETE ALL MENTIONS OF A WORD----\n");
        printf("Write Tweet Word : ");
        scanf("%s",input);
        printf("%s",input);
        find_users_who_tweeted(vertices,number_of_words,words,input);
        delete_mentions(number_of_words,words,input);
        printf(":: After Modification ::\n");
        find_users_who_tweeted(vertices,number_of_words,words,input);
        printf("Again?(y/n) : ");
        scanf("%s",input2);
    }
            printf("\n\n");

            }else if(select==7){

    char input3[50];
    while(strcmp(input3,"n")!=0){
        printf("\n\n----DELETE ALL USERS WHO MENTIONED A WORD----\n");
        printf("Write Tweet Word : ");
        scanf("%s",input);
        printf("%s",input);
        find_users_who_tweeted(vertices,number_of_words,words,input);
        delete_user_mentions_words(vertices, number_of_words,words,input,total_number);
        printf(":: After Modification ::\n");
        find_users_who_tweeted(vertices,number_of_words,words,input);
        printf("Again?(y/n) : ");
        scanf("%s",input3);
    }
                printf("\n\n");

                }else if(select==8){

    printf("\n\n----FIND STRONGLY CONNECTED COMPONENTS----\n");
    dfs(vertices, total_number);
    Vertex trans_vertices[10000];
    for(int i = 0; i < 10000; i++) {
        Vertex_init(&trans_vertices[i]);
    }
    transpose(trans_vertices,vertices,total_number);
    /*
    printf("Print Vertices!!\n");
    for (int i = 0; i < total_number; i++) {
        //print_vertex(trans_vertices,i);
        printf("%d %s", trans_vertices[i].f, trans_vertices[i].id);
    }
*/
    reverse_dfs(trans_vertices, total_number);
                    printf("\n\n");

    }
                    else if(select==9){

                    
    printf("\n\n----FIND SHORTEST PATH FROM A GIVEN USER----\n");
    giving_weight(vertices, total_number);
    printf("Write User : ");
    scanf("%s",input);
    printf("%s",input);
    find_shortest_path(vertices, total_number, input);
    
                        printf("\n\n");

                    }else if(select==99){
                        return 0;
                    }
                    else{
                        printf("\n\nNot in Command\n");
                        printf("\n\n");

                    }
    
    }
    return 0;
}





















