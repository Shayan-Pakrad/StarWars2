#include <iostream>

using namespace std;

struct Dart{
    int heal = 1;
    int size = 1;
};
struct Striker{
    int heal = 2;
    int size = 2;
};
struct Wraith{
    int heal = 4;
    int size = 3;
};
struct Banshee{
    int heal = 6;
    int size = 4;
};

void render(int &map_size);
char cell_to_string(int value);

int main(){
    int map_size;
    cin >> map_size;

    render(map_size);


}

void render(int &map_size){

    int map[map_size][map_size] = {};
    map[map_size - 1][(map_size - 1) / 2] = 1;

    for (int ifor = 0; ifor < map_size * 2; ifor++){
        if (ifor % 2 == 0){
            for (int j = 0; j < map_size; ++j) {
                cout << " ---";
            }
            cout << endl;
            continue;
        }

        int i = ifor / 2;
        for (int j = 0; j < map_size; j++){
            cout << "| " << cell_to_string(map[i][j]) << " ";
        }

        cout << "|" << endl;
    }

    for (int j = 0; j < map_size; j++){
        cout << " ---";
    }
    cout << endl;

}

char cell_to_string(int value){
    char cell;
    switch (value){
        case 0:
            cell = ' ';
            break;
        case 1:
            cell = '#';
            break;
        case 2:
            cell = '^';
            break;
        case 3:
            cell = '*';
            break;
    }

    return cell;
}