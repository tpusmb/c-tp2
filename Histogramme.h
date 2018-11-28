//
// Created by no-code-team on 10/26/18.
//

#ifndef TP1C_M1_HISTOGRAMME_H
#define TP1C_M1_HISTOGRAMME_H

#include <iostream>
#include <vector>
#include <exception>
#include <math.h>
#include <algorithm>

class Histogramme {
public:
    Histogramme(){

        histogramme.resize(360);
        histogramme_cumule.resize(360);
        std::fill(histogramme.begin(), histogramme.end(), 0);
    }

    /**
     * Get the equalise value of the input pixel value
     * @param pixel_value Pixel value to equalise
     * @return The equalise value of the input pixel
     */
    int egalisation(int i){
        return static_cast<int>(round(histogramme_cumule[i] * 360));
    }

    template <typename InputIterator>
    void init( InputIterator it, InputIterator itE ){
        int img_size = 0;
        // Make the histogram
        while (it != itE ){
            histogramme[(int)*it]++;
            ++it;
            img_size++;
        }
        // Cumulative histogram
        histogramme_cumule[0] = histogramme[0];
        for(int index_histo = 1; index_histo < histogramme.size(); index_histo++)
            histogramme_cumule[index_histo] = histogramme_cumule[index_histo - 1] + histogramme[index_histo];

        int max_val = *max_element(histogramme.begin(), histogramme.end());
        // Normalisation between 0 and 1
        for(int index_histo = 0; index_histo < histogramme.size(); index_histo++) {
            histogramme_cumule[index_histo] /= img_size;
            histogramme[index_histo] = static_cast<int>(round((histogramme[index_histo] * 255.0) / (double)max_val));
        }

    }

    /// Geter
    std::vector<int> hist(){ return histogramme; }
    std::vector<double> hist_cumul(){ return histogramme_cumule; }

private:

    // Histogram of the image value beteween 0 and 255 where 255 is the max value in the Histogram
    std::vector<int> histogramme;
    // Cumulative histogram normalisation between 0 and 1
    std::vector<double> histogramme_cumule;
};

#endif //TP1C_M1_HISTOGRAMME_H
