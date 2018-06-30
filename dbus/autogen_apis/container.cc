#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "boost/variant.hpp"

/*
[kv]
Array of maps
Where value is a variant

Map: No 2 elements can have the same key, ie, keys are unique

Variants are a c++17 feature.
Variants need to know the list of permissible types up front.

 */



bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

void kv_test();
void kv_test_recursive();

int main ()
{
  //  std::variant<int, float> v, w;
  std::map<std::string,std::string> kv;
  std::map<std::string,int> node;

  kv["audio"]="volume";
  kv["bb"]="light";

  node["volume"] = 4;
  node["light"] = 5;

  std::cout << "First ints: " << std::endl;
// show content:
  for (std::map<std::string,std::string>::iterator it=kv.begin(); it!=kv.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
  }

  std::cout << "Node[First [\"bb\"]] = " << node[kv["bb"]] << std::endl;
  
  kv_test();
  kv_test_recursive();

  return 0;
}

/*
kv where v could be another kv

key = "audio_status", v is of type audio_status
audio_status type looks like this array:
  "master_volume" = 0.5   // terminating node
  "left speaker" = now the value is another array of kv:
       "volume" = 0.3
       "mute" = false
  "right speaker" = 
       "volume" = 0.4
       "mute" = true

To build my message:
std::map<string, string> msg; msg["audio"]="mute"
Then ipc.emit(msg)

vector<map<string,variant>> right_speaker;
right_speaker.insert(std::make_pair("volume", 0.4))
right_speaker.insert(std::make_pair("mute", true))  // NB different type, implies discriminated union, or variant
vector<map<string,variant>> left_speaker;
left_speaker.insert(std::make_pair("volume", 0.3))
left_speaker.insert(std::make_pair("mute", false))

vector<map<string,variant>> audio_status
audio_status.insert(std::make_pair("left_speaker", left_speaker))
audio_status.insert(std::make_pair("right_speaker", right_speaker))

std::map<string, variant> msg; msg["audio_status"]=audio_status;
Then ipc.emit(msg)


 */
void kv_test()
{

  /*  typedef union val {
    //    std::string str;
    double dval;
  } uval;
  */

  //  std::vector<std::map<std::string,val>> right_speaker;
    
  //  std::map<std::string, val> right_speaker;
  //    uval testv;
  //testv.dval = 0.5;

    std::cout << "Boost variant experiments" <<std::endl;
    std::cout << "Implement kv pairs where each v cannot be a variant. " << std::endl;
    std::cout << "This is options if each key must be fully qualified " << std::endl;
    std::cout << "Eg, audio_status.left_speaker.volume = 50, "  << std::endl;
    std::cout << "    audio_status.left_speaker.mute = false, "  << std::endl;
    std::cout << "    audio_status.global_volume = 20, "  << std::endl;

    boost::variant< int, std::string > v;
    v = "hello";
    std::cout << "Variant outputs " << v << std::endl;

    typedef boost::variant< int, std::string, double > val;
    std::map<std::string, val> right_speaker;
    std::map<std::string, val> left_speaker;

    right_speaker.insert(std::make_pair("name", "right speaker"));
    right_speaker.insert(std::make_pair("volume", 50.10));
    right_speaker.insert(std::make_pair("mute", false));

    std::cout << "Now read out the list of variant values from each key:\n" << std::endl;
  for (std::map<std::string,val>::iterator it=right_speaker.begin(); it!=right_speaker.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
  }

    left_speaker.insert(std::make_pair("name", "left speaker"));
    left_speaker.insert(std::make_pair("volume", 45));
    left_speaker.insert(std::make_pair("mute", true));

    std::cout << "Now read out the list of variant values from each key for left speaker:\n" << std::endl;
  for (std::map<std::string,val>::iterator it=left_speaker.begin(); it!=left_speaker.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
  }

  std::vector<std::map<std::string,val> > audio_status;
  //  audio_status.insert(std::make_pair("left_speaker", left_speaker));
  // Cannot for now add a left_speaker to my vector

}

template <typename ValTag> struct val;

void kv_test_recursive() {
  std::cout << std::endl << "      **********   " <<std::endl;
    std::cout << "Boost variant experiments" <<std::endl;
    std::cout << "Implement kv pairs where each v can be a variant. " << std::endl;
    std::cout << "In this option each key does not need to be fully qualified " << std::endl;
    std::cout << "Eg, {audio_status.{left_speaker.{volume = 50}}, "  << std::endl;
    std::cout << "    {audio_status.{left_speaker.{mute = false}}, "  << std::endl;
    std::cout << "    {audio_status.{global_volume = 20}}, "  << std::endl;

    typedef boost::make_recursive_variant < 
      int, 
      std::string, 
      double,
            std::vector< boost::recursive_variant_ >
      > ::type val;

    std::map<std::string, val> right_speaker;
    std::map<std::string, val> left_speaker;

    // ALERT - I want to try experiment with recursive_wrapper<>


    right_speaker.insert(std::make_pair("volume", 50.10));
    right_speaker.insert(std::make_pair("mute", false));
    right_speaker.insert(std::make_pair("name", "right speaker"));

    //    std::cout << "rs [\"name\"]] = " << right_speaker["name"] << std::endl;
    std::map<std::string, val>::iterator it;
    it = right_speaker.begin();
    std::cout << it->first;
    //    std::cout << it->second;  // Why does this fail?


    std::cout << "Now read out the list of variant values from each key:\n" << std::endl;
  for (std::map<std::string,val>::iterator it=right_speaker.begin(); it!=right_speaker.end(); ++it) {
    //    std::cout << it->first << " => " << it->second << '\n';
  }
#if 0

    left_speaker.insert(std::make_pair("name", "left speaker"));
    left_speaker.insert(std::make_pair("volume", 45));
    left_speaker.insert(std::make_pair("mute", true));

    std::cout << "Now read out the list of variant values from each key for left speaker:\n" << std::endl;
  for (std::map<std::string,val>::iterator it=left_speaker.begin(); it!=left_speaker.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';
  }

  std::vector<std::map<std::string,val> > audio_status;
  //  audio_status.insert(std::make_pair("left_speaker", left_speaker));
  // Cannot for now add a left_speaker to my vector
#endif
}
