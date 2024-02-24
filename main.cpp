#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

struct Enemy{
    string name;
    int x;
    int y;
    int health;
    int size;
};
struct Spaceship{
    int x;
    int y;
    int health;
};
struct Bullet{
    int x;
    int y;
};
struct Game{
    int map_size;
    int point;
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
void move_spaceship_down(Game &game);
void check_bullet_enemy_collision(Game &game);
bool check_spaceship_enemy_collision(Game &game);
void check_enemy_border_collision(Game &game);
Enemy create_enemy(int &map_size);
void render_map(Game &game);
char cell_to_string(int value);
void check_spaceship_health(int &spaceship_health);
void game_over();
void check_points(Game &game);
void save_game(Game &game);
void load_game(Game &game);


int main(){

    start_game();
}

void start_game(){
    system("cls");
    
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
        load_game(game);
        play_game(game);

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
    game.spaceship.health = 3;
    game.enemy = create_enemy(game.map_size);
    game.point = 0;
}

void play_game(Game &game){
    
    render_map(game);
    
    char spaceship_direction;
    while (true){
        cin >> spaceship_direction;

        switch (spaceship_direction){
            case 'a':
                move_spaceship_left(game); break;
            case 'd':
                move_spaceship_right(game); break;
            case 's':
                move_spaceship_down(game); break;
            case 'm':
                start_game(); break;
        }
        render_map(game);
    }
    
}

void move_spaceship_left(Game &game){
    if (game.spaceship.y > 0){

        game.spaceship.y--;

        if (check_spaceship_enemy_collision(game)){
            game.spaceship.y++;
            return;
        }

        Bullet new_bullet;
        new_bullet.x = game.spaceship.x - 1;
        new_bullet.y = game.spaceship.y;

        game.enemy.x++;


        move_bullets(game.bullets);

        game.bullets.push_back(new_bullet);

        check_bullet_enemy_collision(game);

        check_enemy_border_collision(game);

        check_spaceship_health(game.spaceship.health);

        check_points(game);

        save_game(game);
    }
}
void move_spaceship_right(Game &game){

    if (game.spaceship.y < game.map_size - 1){
        
        game.spaceship.y++;

        if (check_spaceship_enemy_collision(game)){
            game.spaceship.y--;
            return;
        }
        
        Bullet new_bullet;
        new_bullet.x = game.spaceship.x - 1;
        new_bullet.y = game.spaceship.y;

        game.enemy.x++;

        move_bullets(game.bullets);

        game.bullets.push_back(new_bullet);

        check_bullet_enemy_collision(game);

        check_enemy_border_collision(game);

        check_spaceship_health(game.spaceship.health);

        check_points(game);

        save_game(game);
        
    }
}

void move_spaceship_down(Game &game){

    if (check_spaceship_enemy_collision(game)){
        return;
    }
    Bullet new_bullet;
    new_bullet.x = game.spaceship.x - 1;
    new_bullet.y = game.spaceship.y;

    game.enemy.x++;


    move_bullets(game.bullets);

    game.bullets.push_back(new_bullet);

    check_bullet_enemy_collision(game);

    check_enemy_border_collision(game);

    check_spaceship_health(game.spaceship.health);

    check_points(game);

    save_game(game);

}

void move_bullets(vector<Bullet> &bullets){

    int bullets_size = bullets.size();

    for (int i = 0;  i < bullets_size; i++){
        bullets[i].x--;

        if (bullets[i].x < 0){
            bullets.erase(bullets.begin() + i);
            i--;
            bullets_size--;
        }
    }
    
}

void check_bullet_enemy_collision(Game &game){

    int bullets_size = game.bullets.size();

    for (int i = 0;  i < bullets_size - 1; i++) {
        for (int x = game.enemy.x - 1; x < game.enemy.x + game.enemy.size; x++){
            for (int y = game.enemy.y; y < game.enemy.y + game.enemy.size; y++){
                if (game.bullets[i].x == x && game.bullets[i].y == y){
                    game.enemy.health--;
                    game.bullets.erase(game.bullets.begin() + i);
                    i--;
                    bullets_size--;
                }
            }
        }
    }

    if (game.enemy.health <= 0){
        game.point += (game.enemy.size * game.enemy.size) * 2;
        game.enemy = create_enemy(game.map_size);
    }

}

bool check_spaceship_enemy_collision(Game &game){

    for (int x = game.enemy.x - 1; x <= game.enemy.x + game.enemy.size; x++){
        for (int y = game.enemy.y; y < game.enemy.y + game.enemy.size; y++){
            if (game.spaceship.x == x && game.spaceship.y == y){
                game.spaceship.health--;
                game.enemy = create_enemy(game.map_size);
                return true;
            }
        }
    }
    return false;
}

void check_enemy_border_collision(Game &game){
    if(game.enemy.x + game.enemy.size >= game.map_size){
        game.spaceship.health--;
        game.enemy = create_enemy(game.map_size);
    }
}

void check_spaceship_health(int &spaceship_health){

    if (spaceship_health <= 0){
        game_over();
    }

}

void check_points(Game &game){
    if (game.point >= game.target_point){
        system("cls");
        cout << "You scored : " << game.point << endl;
        cout << "Your previous target point : "<< game.target_point << endl << endl;
        cout << "You reached your target point!! (enter 0 to exit)" << endl << endl << "enter new target point : ";
        
        int new_target_point;
        cin >> new_target_point;

        while (new_target_point < game.point + 1){
            system("cls");
            cout << "You scored : " << game.point << endl;
            cout << "Your previous target point : "<< game.target_point << endl << endl;
            cout << "Enter a higher target point!! (enter 0 to exit)" << endl << endl << "enter new target point : ";
            cin >> new_target_point;
        }

        game.target_point = new_target_point;

    }
}

void save_game(Game &game){
    /* saved file format:
        enemy.name
        enemy.x
        enemy.y
        enemy.health
        enemy.size
        spaceship.x
        spaceship.y
        spaceship.health
        game.map_size
        game.point
        game.target_point
        numbers of bullets
        bullet.x
        bullet.y
        ...
    */
    ofstream fout("game.txt");

    fout << game.enemy.name << endl;
    fout << game.enemy.x << endl;
    fout << game.enemy.y << endl;
    fout << game.enemy.health << endl;
    fout << game.enemy.size << endl;

    fout << game.spaceship.x << endl;
    fout << game.spaceship.y << endl;
    fout << game.spaceship.health << endl;

    fout << game.map_size << endl;
    fout << game.point << endl;
    fout << game.target_point << endl;

    fout << game.bullets.size() << endl;

    for (int i = 0; i < game.bullets.size(); i++){
        fout << game.bullets[i].x << endl;
        fout << game.bullets[i].y << endl;
    }

    fout.close();

}

void load_game(Game &game){
    ifstream fin("game.txt");

    fin >> game.enemy.name;
    fin >> game.enemy.x;
    fin >> game.enemy.y;
    fin >> game.enemy.health;
    fin >> game.enemy.size;

    fin >> game.spaceship.x;
    fin >> game.spaceship.y;
    fin >> game.spaceship.health;

    fin >> game.map_size;
    fin >> game.point;
    fin >> game.target_point;

    int num_of_bullets;

    fin >> num_of_bullets;

    Bullet bullet;
    for (int i = 0; i < num_of_bullets; i++){
        fin >> bullet.x;
        fin >> bullet.y;

        game.bullets.push_back(bullet);
    }

    fin.close();
}

Enemy create_enemy(int &map_size){
    
    srand(time(0));

    Enemy new_enemy;

    int random_number = rand() % 4;

    switch(random_number){
        case 0:
            new_enemy.name = "Dart";
            new_enemy.size = 1;
            new_enemy.health = 1;
            new_enemy.x = 0;
            new_enemy.y = rand() % (map_size - new_enemy.size - 1);
            break;

        case 1:
            new_enemy.name = "Striker";
            new_enemy.size = 2;
            new_enemy.health = 2;
            new_enemy.x = 0;
            new_enemy.y = rand() % (map_size - new_enemy.size - 1);
            break;

        case 2:
            new_enemy.name = "Wraith";
            new_enemy.size = 3;
            new_enemy.health = 4;
            new_enemy.x = 0;
            new_enemy.y = rand() % (map_size - new_enemy.size - 1);
            break;

        case 3:
            new_enemy.name = "Banshee";
            new_enemy.size = 4;
            new_enemy.health = 6;
            new_enemy.x = 0;
            new_enemy.y = rand() % (map_size - new_enemy.size - 1);   
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

    // showing informations above map

    cout << endl << "map size: " << game.map_size;
    cout << "  spaceship health: " << game.spaceship.health;
    cout << "  enemy health: " << game.enemy.health;
    cout << "  score: " << game.point;
    cout << "  target point: " << game.target_point << endl << endl;

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


void game_over(){
    system("cls");

    cout << "Game Over";

    char game_over;

    cin >> game_over;

    exit(0);
}