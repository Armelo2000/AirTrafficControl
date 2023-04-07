/*
 * DataParser.cpp
 *
 *  Created on: 05.04.2023
 *      Author: melah
 */

#include "inc/DataParser.h"

/* -----------------------------------------------------------------------------
 * Name:        DataParser
 * Input:       const char* aircraftDataFile
 * Output:      None.
 * Description: The Parser constructor which takes in the path of the aircraft
 *              data file and then begins parsing the data.
 * -----------------------------------------------------------------------------
 */
DataParser::DataParser(const char* aircraftDataFile) {

    this->m_aircraftDataFile = aircraftDataFile;

    parse();
}
/* -----------------------------------------------------------------------------
 * Name:        parse
 * Input:       None.
 * Output:      None.
 * Description: This functions reads aircraft data from a file with a specific
 *              format,where each line represents data for an aircraft,
 *              and creates an Aircraft object for each line. Each object is
 *              added to a vector of Aircraft objects called aircraftSchedule.
 * -----------------------------------------------------------------------------
 */
int DataParser::parse() {

    int flight_id, time_at_boundary, pos_x, pos_y, pos_z, speed_x, speed_y, speed_z;

    FILE *input_file = fopen(m_aircraftDataFile, "r");
    if (input_file == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }

    // Read each line of the input file until the end of file
    while (fscanf(input_file, "%d,%d,%d,%d,%d,%d,%d,%d\n", &time_at_boundary, &flight_id, &pos_x, &pos_y,&pos_z, &speed_x, &speed_y, &speed_z) == 8) {

        // Create an Aircraft object with the extracted data and add it to the aircraftSchedule vector
        //Aircraft aircraft(time_at_boundary, flight_id, pos_x, pos_y, pos_z, speed_x, speed_y, speed_z);
    	Aircraft aircraft(time_at_boundary, flight_id, pos_x, pos_y, pos_z, speed_x, speed_y, speed_z);
        m_aircraftSchedule.push_back(aircraft);
    }

    /* Close the file */
    fclose(input_file);

    return EXIT_SUCCESS;
}
/* -----------------------------------------------------------------------------
 * Name:        getAircraftSchedule
 * Input:       None.
 * Output:      None.
 * Description: This functions returns the aircraftSchedule vector.
 * -----------------------------------------------------------------------------
 */
vector<Aircraft> DataParser::getAircraftSchedule() {

    return m_aircraftSchedule;
}

DataParser::~DataParser() {
    // TODO Auto-generated destructor stub
}
