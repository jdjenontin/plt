#include <iostream>
#include <SFML/Network.hpp>

#include <vector>

using namespace std;
using namespace sf;

int main()
{
    bool done = false;
    short int port = 2000;

    TcpListener listener;
    SocketSelector selector;

    if(listener.listen(port) == Socket::Done){
        cout << "Serveur correctement lancé !" << endl;
    } else {
        exit(0);
    }
    selector.add(listener);

    vector<TcpSocket*> Clients;

    while(!done)
    {
        if(selector.wait())
        {
            if(selector.isReady(listener))
            {
                TcpSocket *socket = new TcpSocket();
                listener.accept(*socket);
                selector.add(*socket);
                Clients.push_back(socket);

                Packet receivePacket;
                if(socket->receive(receivePacket) == Socket::Done)
                {
                    string pseudo;
                    receivePacket >> pseudo;
                    cout << pseudo << " vient de se connecter. " << endl;

                }
            } else {
                for (int i = 0; i < Clients.size(); i++) 
                {
                    if(selector.isReady(*Clients[i])){
                        Packet receivePacket;
                        if(Clients[i]->receive(receivePacket) == Socket::Done){
                            string pseudo;
                            int x, y;
                            receivePacket >> pseudo >> x >> y;

                            cout << "Reçu du client " << pseudo << " x : " << x << " y : "<< y << endl;

                            Packet sendPacket;
                            sendPacket << pseudo << x << y;

                            for (int j = 0; j < Clients.size(); j++)
                            {
                                if(i != j)
                                {
                                    Clients[j]->send(sendPacket);
                                }
                            }

                        }

                    }
                }
            }
        }
    }

    return 1;
}