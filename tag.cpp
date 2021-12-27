#include <string.h>
#include <fileref.h>

#include <tag.h>
#include <tpropertymap.h>

using namespace std;

void usage(void)
{
    cerr << "Usage:" << endl;
    cerr << "  tag FILE [FLAG]" << endl;
    cerr << "Flags:" << endl;
    cerr << "  -a ARTIST  Set the artist" << endl;
    cerr << "  -t TITLE   Set the title" << endl;
    cerr << "  -A ALBUM   Set the album" << endl;
    cerr << "  -g GENRE   Set the genre" << endl;
    cerr << "  -y YEAR    Set the year" << endl;
    cerr << "  -T TRACK   Set the track" << endl;
}

bool check_flag(char *arg, char flag)
{
    return strlen(arg) == 2 && arg[1] == flag;
}

TagLib::String fetch_arg(int argc, char **argv, int *i)
{
    if (*i == argc - 1) {
        usage();
        cerr << "Error: no argument provided to flag `" << argv[*i] << "`" << endl;
        exit(1);
    }

    *i += 1;
    return argv[*i];
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        cerr << "Error: no file provided" << endl;
        exit(1);
    }

    TagLib::FileRef f(argv[1]);
    auto *t = f.tag();

    for (auto i = 2; i < argc; ++i) {
        if (check_flag(argv[i], 'a')) {
            t->setArtist(fetch_arg(argc, argv, &i));
        } else if (check_flag(argv[i], 't')) {
            t->setTitle(fetch_arg(argc, argv, &i));
        } else if (check_flag(argv[i], 'A')) {
            t->setAlbum(fetch_arg(argc, argv, &i));
        } else if (check_flag(argv[i], 'g')) {
            t->setGenre(fetch_arg(argc, argv, &i));
        } else if (check_flag(argv[i], 'y')) {
            t->setYear(fetch_arg(argc, argv, &i).toInt());
        } else if (check_flag(argv[i], 'T')) {
            t->setTrack(fetch_arg(argc, argv, &i).toInt());
        } else {
            usage();
            cerr << "Error: invalid flag `" << argv[i] << "`" << endl;
            exit(1);
        }
    }

    if (!f.file()->save()) {
        cerr << "Error: could not write tags to file `" << argv[1] << "`" << endl;
        exit(1);
    }
}
