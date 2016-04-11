#include <iostream>
#include<algorithm>
#include <string>
#include <functional>
using namespace std;

// Find maximum number of intersecting intervals (Correct solution)

double convert(int hour, int minutes){
	return hour + (minutes*.01);
}

int main(){
	
	int n;
	int hour, minutes;
	char colon;
	
	// process input - ok
	std::cin >> n;
	double arrival[n];
	double departure[n];
    for (int i=0; i<n; ++i){
		std::cin >> hour >> colon >> minutes;
		arrival[i] = convert(hour,minutes);
        std::cin >> hour >> colon >> minutes;
		departure[i] = convert(hour,minutes);
    }
	
	// find maximum number of overlapping arrays
	sort(arrival, arrival+n);
	sort(departure,departure+n);
	
	int i=1; // indexes arrivals
	int j=0; // indexes departures
	int platforms = 1;
	int maxPlatforms = 1;
	
	while (i<n && j<n){
		if (arrival[i] < departure[j]){
			platforms++;
			i++;
			if (platforms > maxPlatforms) {
				maxPlatforms = platforms;
			}
		}
		else{
			platforms--;
			j++;
		}
	}
	
	cout << "maximum number of platforms: " << maxPlatforms << endl;
	return 0;
}
