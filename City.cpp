#include "City.h"

City::City() {};
City::~City() = default;

double City::deg_rad(double deg)
{
	return (deg * M_PI / 180.0);

}

double City::haversine_distance(double latitude1, double longitude1, double latitude2, double longitude2)
{
    double lat1 = deg_rad(latitude1);
    double lon1 = deg_rad(longitude1);
    double lat2 = deg_rad(latitude2);
    double lon2 = deg_rad(longitude2);

    double d_lat = abs(lat1 - lat2);
    double d_lon = abs(lon1 - lon2);

    double a = pow(sin(d_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(d_lon / 2), 2);

    //double d_sigma = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d_sigma = 2 * asin(sqrt(a));

    return earth_radius_km * d_sigma;
}


void City::fillVector(vector<City>& Index)
{
    string input;
    City city;
    fstream file;
    int count = 1;
    file.open("worldcities.csv", ios::in);
    getline(file, input, '\n'); //ignores the header of file
    while (!file.eof())
    {
   
        //Grab information from each line of file as string
        getline(file, input, ',');
        city.setName(input);
        getline(file, input, ',');
        city.setCountry(input);
        getline(file, input, ',');
        city.setLat(input);
        getline(file, input);
        city.setLon(input);
        city.setID(to_string(count));
        Index.push_back(city);
       count++;
    }
    Index.pop_back(); // There is an empty string at the end of the file, this removes it
}
void City::printVector(vector<City>& Index) {
    int size = Index.size();
    sort(Index.begin(), Index.end(), [](City& lhs, City& rhs) {return lhs.getDistance() < rhs.getDistance(); }); //Sort array


    cout << "Top 5 closest cities: " << endl;
    for (int i = 2; i <= 6; i++) //Print 5 largest distances, starting at 2 to exclude itself
    {

        if (Index[i].getName() != "") {
            cout << "Name: " << Index[i].getName() << " Distance: " << Index[i].getDistance() << "km " << "or " << Index[i].getDistance() * 0.62137 << "mi" << endl;
        }

    }

    cout << "Top 5 farthest cities: " << endl;
    for (int i = Index.size() - 5; i < Index.size(); i++) //Print 5 smallest distances
    {
        if (Index[i].getName() != "") {
            cout << "Name: " << Index[i].getName() << " Distance: " << Index[i].getDistance() << "km " << "or " << Index[i].getDistance()* 0.62137 << "mi" << endl;
        }
    }

}
void City::loop(vector<City>& Index)
{
    City city;
    string choice;
    bool loop = true;
    bool flag = false;
    while (loop) {
        cout << "Please enter a city Index #, Name, or quit: ";
        getline(cin, choice);
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower); //Case insenitivity
        std::ofstream out("result.txt", fstream::app);
        std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect cout to out.txt
        if (choice == "quit") {
            exit(EXIT_FAILURE);
        }
        else
            for (int i = 0; i < Index.size(); i++) { //search array
                string tempName = Index[i].getName();
                transform(tempName.begin(), tempName.end(), tempName.begin(), ::tolower); //Case insenitivity

                if (choice == tempName) {

                    cout << endl << "Your city choice was: " << tempName << endl;
                    Index[i].calcDistances(Index[i].getLat(), Index[i].getLon(), Index);
                    city.printVector(Index); // print
                    flag = true;


                }
                else if ((choice) == Index[i].getID()) {
 
                    cout << endl << "Your city choice was by ID was: " << Index[i].getName() << endl;
                    Index[i].calcDistances(Index[i].getLat(), Index[i].getLon(), Index);
                    city.printVector(Index);
                    flag = true;
                }

                }
        cout.rdbuf(coutbuf); //reset to standard output again

        if (flag == false) {
            cout << "Please enter a valid input" << endl;
        }
        flag = false;
            
        }
    
}
void City::calcDistances(string choiceLat, string choiceLon, vector<City>& Index)
{
    const int size = Index.size(); //replace with an iterator
    for (int i = 0; i < size-1; i++)
    {
        double lat = stod(Index[i].getLat());
        double lon = stod(Index[i].getLon());
        double tempDistance = Index[i].haversine_distance(stod(choiceLat), stod(choiceLon), lat, lon);

        Index[i].setDistance(tempDistance);
    }

}
string City::getName()
{
    return name;
}

string City::getCountry()
{
    return country;
}

string City::getLat()
{
    return lat;
}

string City::getLon()
{
    return lon;
}

string City::getID()
{
    return ID;
}

double City::getDistance()
{
    return distance;
}

void City::setName(string name)
{
    this->name = name;
}

void City::setCountry(string country)
{
    this->country = country;
}

void City::setLat(string lat)
{
    this->lat = lat;
}

void City::setLon(string lon)
{
    this->lon = lon;
}

void City::setID(string ID)
{
    this->ID = ID;
}

void City::setDistance(double distance)
{
    this->distance = distance;
}
