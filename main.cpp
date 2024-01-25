// Section 20
// Challenge 2
//  Lists

#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <string>

class Song {
  friend std::ostream &operator<<(std::ostream &os, const Song &s);
  std::string name;
  std::string artist;
  int rating;

public:
  Song() = default;
  Song(std::string name, std::string artist, int rating)
      : name{name}, artist{artist}, rating{rating} {}
  std::string get_name() const { return name; }
  std::string get_artist() const { return artist; }
  int get_rating() const { return rating; }

  bool operator<(const Song &rhs) const { return this->name < rhs.name; }

  bool operator==(const Song &rhs) const { return this->name == rhs.name; }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
  os << std::setw(20) << std::left << s.name << std::setw(30) << std::left
     << s.artist << std::setw(2) << std::left << s.rating;
  return os;
}

void display_menu() {
  std::cout << "\nF - Play First Song" << std::endl;
  std::cout << "N - Play Next song" << std::endl;
  std::cout << "P - Play Previous song" << std::endl;
  std::cout << "A - Add and play a new Song at current location" << std::endl;
  std::cout << "L - List the current playlist" << std::endl;
  std::cout << "===============================================" << std::endl;
  std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
  // This function should display
  // Playing: followed by the song that is playing
  std::cout << "Playing......" << std::endl;
  std::cout << song << std::endl;
  std::cout << "===============================================" << std::endl;
}

void display_playlist(const std::list<Song> &playlist,
                      const Song &current_song) {
  // This function should display the current playlist
  // and then the current song playing.
  std::cout << "\n\n\n\n\n\n\n\n\n\n";
  play_current_song(current_song);
  for (const auto &song : playlist) {
    std::cout << song << std::endl;
  }
}

void add_song(std::list<Song> &playlist,
              std::list<Song>::iterator &current_song) {
  std::string name{};
  std::string artist{};
  int rating{};
  std::cout << "Please put the name of the song to be added." << std::endl;
  std::cin >> name;
  std::cout << "Please put the artist of the song to be added." << std::endl;
  std::cin >> artist;
  std::cout << "Please put the rating of the song to be added." << std::endl;
  std::cin >> rating;
  playlist.insert(current_song, {name, artist, rating});
  std::advance(current_song, -1);
  display_playlist(playlist, *current_song);
}

int main() {

  std::list<Song> playlist{{"God's Plan", "Drake", 5},
                           {"Never Be The Same", "Camila Cabello", 5},
                           {"Pray For Me", "The Weekend and K. Lamar", 4},
                           {"The Middle", "Zedd, Maren Morris & Grey", 5},
                           {"Wait", "Maroone 5", 4},
                           {"Whatever It Takes", "Imagine Dragons", 3}};

  std::list<Song>::iterator current_song = playlist.begin();

  // std::cout << "To be implemented" << std::endl;
  //  Your program logic goes here
  char selection{};
  do {
    display_playlist(playlist, *current_song);
    display_menu();
    std::cin >> selection;
    switch (::toupper(selection)) {
    case 'F': {
      std::cout << "Playing first song : " << std::endl;
      current_song = playlist.begin();
      display_playlist(playlist, *current_song);
      break;
    }
    case 'N': {
      std::cout << "Playing next song : " << std::endl;
      if (current_song == playlist.end()) {
        std::cout << "Wrapping to beginning of playlist : " << std::endl;
        current_song = playlist.begin();
      } else {
        std::advance(current_song, 1);
      }
      display_playlist(playlist, *current_song);
      break;
    }
    case 'P': {
      std::cout << "Playing previous song..." << std::endl;
      if (current_song == playlist.begin()) {
        std::cout << "Wrapping to end of playlist : " << std::endl;
        current_song = playlist.end();
      } else {
        std::advance(current_song, -1);
      }
      display_playlist(playlist, *current_song);
      break;
    }
    case 'A': {
      add_song(playlist, current_song);
      break;
    }
    case 'L': {
      display_playlist(playlist, *current_song);
      break;
    }
    default: {
      std::cout << "Invalid command, retry" << std::endl;
      break;
    }
    }
  } while (::toupper(selection) != 'Q');

  std::cout << "Thanks for listening!" << std::endl;
  return 0;
}