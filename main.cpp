
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string>
#include <algorithm>
#include <fstream>

#include "DNSpgDBiface.h"

using namespace std;



int main(int argc, char *argv[])
{
    PGconn          *conn;
    string host, dbname, user, passwd, mode;
    fstream cf;


    if(3<argc){
        cf.open(argv[1], std::fstream::in);
        cf >> host;
        cf >> dbname;
        cf >> user;
        cf >> passwd;
        cf.close();

        conn = PQconnectdb(("dbname="+dbname+" host="+host+" user="+user+" password="+passwd).c_str());
        if (PQstatus(conn) == CONNECTION_BAD) {
            cout << "-3 (We were unable to connect to the database)" << endl;
            return 0;
        }

        mode = argv[2];
        if("add" == mode){
            if(4==argc){
                cout << adduri(conn, argv[3], "") << endl;
            }else if(5==argc){
                cout << adduri(conn, argv[3], argv[4]) << endl;
            }else if(6==argc){
                cout << adduri(conn, argv[3], argv[4], argv[5]) << endl;
            }else if(7==argc){
                cout << adduri(conn, argv[3], argv[4], argv[5], atoi(argv[6])) << endl;
            }
        }else if("del"==mode){
            cout << deluris(conn, argv[3]) << endl;
        }
        return 0;
    } else {
        cout << "USAGE:" << endl;
        cout << endl;
        cout << "  smartRNS_DNS_DB_iface configfile, cmd, uri, content, [type], [ttl]" << endl << endl;
        return 0;

    }


    PQfinish(conn);

    return 0;
}
