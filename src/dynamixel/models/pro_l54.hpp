#ifndef DYNAMIXEL_PRO_L54_HPP_
#define DYNAMIXEL_PRO_L54_HPP_

#include <stdint.h>

#include "servo_model.hpp"
#include "../protocol1.hpp"

namespace dynamixel {
namespace models {
    class ProL54;

    template<>
    struct ModelTraits<ProL54> {
        typedef Protocol2 protocol_t;

        struct CT {
            static const protocol_t::address_t model_number = 0;
            typedef uint16_t model_number_t;
            static const model_number_t model_number_value = 320;
            static const protocol_t::address_t model_info = 2;
            typedef uint32_t model_info_t;
            static const protocol_t::address_t firmware_version = 2;
            typedef uint8_t firmware_version_t;
            static const protocol_t::address_t id = 7;
            typedef protocol_t::id_t id_t;
            static const protocol_t::address_t baudrate = 8;
            typedef uint8_t baudrate_t;
            static const protocol_t::address_t return_delay_time = 9;
            typedef uint8_t return_delay_time_t;
            static const protocol_t::address_t operating_mode = 11;
            typedef uint8_t operating_mode_t;
            static const protocol_t::address_t homing_offset = 13;
            typedef uint32_t homing_offset_t;
            static const protocol_t::address_t moving_threshold = 17;
            typedef uint32_t moving_threshold_t;
            static const protocol_t::address_t highest_temperature_limit = 21;
            typedef uint8_t highest_temperature_limit_t;
            static const protocol_t::address_t highest_voltage_limit = 22;
            typedef uint16_t highest_voltage_limit_t;
            static const protocol_t::address_t lowest_voltage_limit = 24;
            typedef uint16_t lowest_voltage_limit_t;
            static const protocol_t::address_t acceleration_limit = 26;
            typedef uint32_t acceleration_limit_t;
            static const protocol_t::address_t torque_limit = 30;
            typedef uint16_t torque_limit_t;
            static const protocol_t::address_t speed_limit = 32;
            typedef uint32_t speed_limit_t;
            static const protocol_t::address_t max_position_limit = 36;
            typedef uint32_t max_pos_limit_t;
            static const protocol_t::address_t min_position_limit = 40;
            typedef uint32_t min_pos_limit_t;
            static const protocol_t::address_t alarm_shutdown = 48;
            typedef uint8_t alarm_shutdown_t;
            static const protocol_t::address_t torque_enable = 562;
            typedef uint8_t torque_enable_t;
            static const protocol_t::address_t led_r = 563;
            typedef uint8_t led_r_t;
            static const protocol_t::address_t led_g = 564;
            typedef uint8_t led_g_t;
            static const protocol_t::address_t led_b = 565;
            typedef uint8_t led_b_t;
            static const uint8_t led_off = 0;
            static const uint8_t led_on = 255;
            static const protocol_t::address_t goal_position = 596;
            typedef int32_t goal_position_t;
            static const goal_position_t min_goal_pos = -180684;
            static const goal_position_t max_goal_pos = 180684;
            static const protocol_t::address_t moving_speed = 600;
            typedef uint32_t moving_speed_t;
            static const protocol_t::address_t goal_torque = 604;
            typedef int16_t goal_torque_t;
            static const protocol_t::address_t goal_acceleration = 606;
            typedef int32_t goal_acceleration_t;
            static const protocol_t::address_t moving = 610;
            typedef uint8_t moving_t;
            static const protocol_t::address_t present_position = 611;
            typedef uint32_t present_position_t;
            static const protocol_t::address_t present_speed = 615;
            typedef uint32_t present_speed_t;
            static const protocol_t::address_t current = 621;
            typedef uint16_t present_load_t;
            static const protocol_t::address_t present_voltage = 623;
            typedef uint16_t present_voltage_t;
            static const protocol_t::address_t present_temperature = 625;
            typedef uint8_t present_temperature_t;
            static const protocol_t::address_t registered = 890;
            typedef uint8_t registered_t;
            static const protocol_t::address_t status_return_level = 891;
            typedef uint8_t status_return_level_t;
            static const protocol_t::address_t hardware_error_status = 892;
            typedef uint8_t hardware_error_status_t;
        };
    };

    class ProL54 : public ServoModel<ProL54>,
    public RGBLedServoModel<ProL54>,
    public DynRGBLedServoModel<ProL54> {    
    };
}
}

#endif