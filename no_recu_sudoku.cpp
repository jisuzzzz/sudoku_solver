#include <iostream>
using namespace std;

#define pass 1
#define fail 0
#define forward 1
#define backward 0

int grid[9][9] = {0};
int sub_grid[3][3] = {0};

int check_row(int row, int grid[9][9]){
    for (int i=0; i<9; i++){
        for (int j=i+1; j<9; j++){
            if ((grid[row][i] != 0) || (grid[row][j] != 0)){
                if (grid[row][i] == grid[row][j]) return fail;
            }
        }
    }
    return pass;
}

int check_column(int column, int grid[9][9]){
    for (int i=0; i<9; i++){
        for (int j=i+1; j<9; j++){
            if ((grid[i][column] != 0) || (grid[j][column] != 0)){
                if (grid[i][column] == grid[j][column]) return fail;
            }
        }
    }
    return pass;
}
int check_dupl(int arr[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (arr[i] != 0 || arr[j] != 0) {
                if (arr[i] == arr[j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_3x3(int grid[9][9]) {
    int b[9];
    int k = 0;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            for (int row = r * 3; row < ((r + 1) * 3); row++) {
                for (int col = c * 3; col < ((c + 1) * 3); col++) {
                    b[k++] = grid[row][col];
                }
            }
            sub_grid[r][c] = check_dupl(b);
            k = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sub_grid[i][j] == 1)
                return fail;
        }
    }
    return pass;
}

int isPossibleNum(int i, int j, int num) {
    int start_row = i - i % 3;
    int start_col = j - j % 3;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if ((row + start_row) == i && (col + start_col) == j) {
                continue;
            }
            if (grid[row + start_row][col + start_col] == num)
                return fail;
        }
    }
    return pass;
}

int check_elements() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] < 1 || grid[i][j] > 9)
                return fail;
        }
    }
    return pass;
}

int main(){
    int filled = 0;
    int row[81], column[81];
    int flag = 0;
    int dir = forward;

    cout << "Enter numbers : \n";
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cin >> grid[i][j];
        }
    }
    cout << "\n ---Entry finished ---\n";

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(grid[i][j] > 0){
                row[filled] = i;
                column[filled] = j;
                filled++;
            }
        }
    }
    cout << "\n" << " filled : " << filled << "\n";
    for(int i=0; i<9; i++){
        if (check_row(i, grid) == fail) {
            cout << "\n identical numbers in row\n";
            return 0;
        }
        if (check_column(i, grid) == fail) {
            cout << "\n identical numbers in column\n";
            return 0;
        }
    }
    if(check_3x3(grid)==fail){
        cout << "\n identical numbers in box\n";
        return 0;
    }
    cout << "\n";
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){  
            for(int k=0; k<filled; k++){ 
                if((i==row[k]) && (j==column[k])){ 
                    k=0;
                    flag=1;
                    break;
                }
            }
            if(flag==1){ 
                flag=0; 
                if(dir==forward) 
                    continue;
                else {
                    j--;
                    j--;
                    if(j < -1 && i > 0 ){
                        i--;
                        j=7;
                    }
                    continue;
                }
                
            }
            if(dir==backward){
                grid[i][j]++;
                if(grid[i][j]>9){
                    grid[i][j]=0;
                    j--;
                    j--;
                    if(j<-1 && i>0){
                        i--;
                        j=7;
                    }
                    continue;
                }
            }
            while(grid[i][j]<=9){
                if(grid[i][j]==0){
                    grid[i][j] = 1;
                }
                if(check_row(i,grid) & check_column(j,grid) & isPossibleNum(i,j,grid[i][j])){
                    dir = forward;
                    break;
                }
                else{
                    grid[i][j]++;
                    if(grid[i][j]>9){
                        grid[i][j]=0;
                        j--;
                        j--;
                        if(j<-1 && i>0){
                            i--;
                            j=7;
                        }
                        dir = backward;
                        break;
                    }
                }
            }
            if(j < -3){
                cout << "\n No solution";
                return 0;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


