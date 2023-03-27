#include <iostream>
#include <iomanip>
#include "stacker.h"

using namespace std;

int main() {
    string prefix;
    int num_images;
    cout << "Please enter the image you wish to stack: ";
    cin >> prefix;
    cout << "Please enter the number of images: ";
    cin >> num_images;
    cout << "Stacking images:" << endl;
    for (int i = 1; i <= num_images; i++) {
        cout << prefix << "/" << prefix << "_" << setfill('0') << setw(3) << i << ".ppm" << endl;
    }
    Stacker s(prefix + "/" + prefix + "_001.ppm");
    s.stack(prefix, num_images);
    s.save(prefix + ".ppm");
    return 0;
}