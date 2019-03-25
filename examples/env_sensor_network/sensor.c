/**
 * OS dependent. Replace if you use another RTOS.
 */
#include "saul_reg.h"
#include "proto_compiled/DataResponse.pb.h"

saul_reg_t * temp_sensor_reg_entry;
saul_reg_t * hum_sensor_reg_entry;

phydat_t temp_sensor_phydat;
phydat_t hum_sensor_phydat;

environmentSensors_SingleDataPoint temp_data_point;
environmentSensors_SingleDataPoint hum_data_point;

void sensors_init(void){
    temp_sensor_reg_entry = saul_reg_find_type(SAUL_SENSE_TEMP);
    hum_sensor_reg_entry = saul_reg_find_type (SAUL_SENSE_HUM);
}

void sensors_read_values(void){
    saul_reg_read(temp_sensor_reg_entry, &temp_sensor_phydat);
    temp_data_point.value = temp_sensor_phydat.val[0];
    temp_data_point.scale = temp_sensor_phydat.scale;
    saul_reg_read(hum_sensor_reg_entry, &hum_sensor_phydat);
    hum_data_point.value = hum_sensor_phydat.val[0];
    hum_data_point.scale = hum_sensor_phydat.scale;
}

environmentSensors_SingleDataPoint * sensors_get_temp_value(void){
    return &temp_data_point;
}

environmentSensors_SingleDataPoint * sensors_get_hum_value(void){
    return &hum_data_point;
}

