#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Enemy{
    string name;
    int x;
    int y;
    int heal;
    int size;
    int point;
};
struct Spaceship{
    int x;
    int y;
};
struct Bullet{
    int x;
    int y;
};
struct Game{
    int map_size;
    int target_point;
    Spaceship spaceship;
    Enemy enemy;
    vector<Bullet> bullets;
};

void start_game();
int show_menu();
void init_new_game(Game &game);
void play_game(Game &game);
void move_bullets(vector<Bullet> &bullets);
void move_spaceship_left(Game &game);
void move_spaceship_right(Game &game);
void check_collision(Game &game);
Enemy create_enemy(int &map_size);
void render_map(Game &game);
char cell_to_string(int value);

int main(){

    start_game();
}

void start_game(){
    int user_choice = show_menu();

    Game game;
    
    if (user_choice == 1){

        do{
            system("cls");
            cout << "enter the size of map = ";
            cin >> game.map_size;
        }while(game.map_size < 15);

        system("cls");
        cout << "enter the point = ";
        cin >> game.target_point;

        init_new_game(game);
        play_game(game);
    }

    else if (user_choice == 2){

    }

    else if (user_choice == 3){
        exit(0);
    }
}

int show_menu(){
    cout << "Menu:" << endl;
    cout << " 1. start" << endl;
    cout << " 2. load" << endl;
    cout << " 3. exit" << endl;
    int user_choice;
    cin >> user_choice;

    return user_choice;
}

void init_new_game(Game &game){
    game.spaceship.x = game.map_size - 1;
    game.spaceship.y = (game.map_size - 1) / 2;
    game.enemy = create_enemy(game.map_size);
}

void play_game(Game &game){
    
    // Spaceship my_spaceship;
    // vector<Bullet> bullets;

    // my_spaceship.x = map_size - 1;
    // my_spaceship.y = (map_size - 1) / 2;

    // Enemy first_enemy = create_enemy(map_size);

    render_map(game);
    
    char spaceship_direction;
    while (true){
        cin >> spaceship_direction;

        switch (spaceship_direction){
            case 'a':
                move_spaceship_left(game); break;
            case 'd':
                move_spaceship_right(game); break;
        }
        render_map(game);
    }
    
}

void move_bullets(vector<Bullet> &bullets){

    int index_indicator = 0;

    for (Bullet &bullet : bullets){
        bullet.x--;

        if (bullet.x < -2){
            bullets.erase(bullets.begin() + index_indicator); continue;
        }
        index_indicator++;
    }
}

void move_spaceship_left(Game &game){
    if (game.spaceship.y > 0){
        game.spaceship.y--;

        Bullet new_bullet;
        new_bullet.x = game.spaceship.x - 1;
        new_bullet.y = game.spaceship.y;

        move_bullets(game.bullets);

        game.enemy.x++;

        game.bullets.push_back(new_bullet);

        check_collision(game);
    }
}
void move_spaceship_right(Game &game){

    if (game.spaceship.y < game.map_size - 1){
        game.spaceship.y++;
        
        Bullet new_bullet;
        new_bullet.x = game.spaceship.x - 1;
        new_bullet.y = game.spaceship.y;

        move_bullets(game.bullets);

        game.enemy.x++;

        game.bullets.push_back(new_bullet);

        check_collision(game);
        
        
    }
}

void check_collision(Game &game){

    int bullets_size = game.bullets.size();

    for (int i = 0;  i < bullets_size - 1; i++) {
        for (int x = game.enemy.x - 1; x < game.enemy.x + game.enemy.size; x++){
            for (int y = game.enemy.y; y < game.enemy.y + game.enemy.size; y++){
                if (game.bullets[i].x == x && game.bullets[i].y == y){
                    game.enemy.heal--;
                    game.bullets.erase(game.bullets.begin() + i);
                    i--;
                }
            }
        }
    }

}

Enemy create_enemy(int &map_size){
    
    srand(time(0));

    Enemy new_enemy;

    int random_number = rand() % 4;

    switch(random_number){
        case 0:
            new_enemy.name = "Dart";
            new_enemy.size = 1;
            new_enemy.heal = 1;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 1:
            new_enemy.name = "Striker";
            new_enemy.size = 2;
            new_enemy.heal = 2;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 2:
            new_enemy.name = "Wraith";
            new_enemy.size = 3;
            new_enemy.heal = 4;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;
            break;

        case 3:
            new_enemy.name = "Banshee";
            new_enemy.size = 4;
            new_enemy.heal = 6;
            new_enemy.point = new_enemy.size * new_enemy.size;
            new_enemy.x = 0;
            new_enemy.y = rand() % map_size - new_enemy.size - 1;   
            break;    
    }

    return new_enemy;
}

void render_map(Game &game){
    int map[game.map_size][game.map_size] = {};

    
    
    map[game.spaceship.x][game.spaceship.y] = 1;

    for (Bullet &bullet : game.bullets){
        map[bullet.x][bullet.y] = 2;
    }

    for (int i = game.enemy.x; i < game.enemy.x + game.enemy.size; i++){
        for (int j = game.enemy.y; j < game.enemy.y + game.enemy.size; j++){
            map[i][j] = 3;
        }
    }


    system("cls");
    
    cout << game.enemy.heal << endl;
    for (int ifor = 0; ifor < game.map_size * 2; ifor++){
        if (ifor % 2 == 0){
            for (int j = 0; j < game.map_size; ++j) {
                cout << " ---";
            }
            cout << endl;
            continue;
        }

        int i = ifor / 2;
        for (int j = 0; j < game.map_size; j++){
            cout << "| " << cell_to_string(map[i][j]) << " ";
        }

        cout << "|" << endl;
    }

    for (int j = 0; j < game.map_size; j++){
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