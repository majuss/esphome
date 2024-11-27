import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import maybe_simple_id
from esphome.components import uart, binary_sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_WINDOW,
    CONF_ADDRESS,
    CONF_NAME

    # BINA
)

DEPENDENCIES = ["uart"]

# CONF_AUTOMATIC_BASELINE_CALIBRATION = "automatic_baseline_calibration"

enocean_ns = cg.esphome_ns.namespace("enocean")
Enocean = enocean_ns.class_("Enocean", cg.PollingComponent, uart.UARTDevice)
# MHZ19CalibrateZeroAction = mhz19_ns.class_(
#     "MHZ19CalibrateZeroAction", automation.Action
# )

# PLATFORM_SCHEMA = BINARY_SENSOR_PLATFORM_SCHEMA.extend(
#     {
#         vol.Required(CONF_ID): vol.All(cv.ensure_list, [vol.Coerce(int)]),
#         vol.Optional(CONF_NAME, default=DEFAULT_NAME): cv.string,
#         vol.Optional(CONF_DEVICE_CLASS): DEVICE_CLASSES_SCHEMA,
#     }
# )


CONFIG_SCHEMA = (
    cv.Schema(
       {
            cv.GenerateID(): cv.declare_id(Enocean),
            cv.Required(CONF_ADDRESS): cv.ensure_list(cv.hex_int),
            cv.Optional(CONF_NAME, default="Enocean Sensor"): cv.string,
            cv.Optional("device_class", default=DEVICE_CLASS_WINDOW): cv.string,
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)




async def to_code(config):
    # full_id = config[CONF_ID]  # This is [0xfe, 0xea, 0x72, 0x79]

    # Create a new instance of Enocean and pass the full ID
    var = cg.new_Pvariable(config[CONF_ID])  # Pass the full ID list
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)


    sens = await binary_sensor.new_binary_sensor(config)
    cg.add(var.set_sensor(sens))
    cg.add_library("majuss/EnOcean", None)

    # if CONF_CO2 in config:
    #     sens = await sensor.new_sensor(config[CONF_CO2])
    #     cg.add(var.set_co2_sensor(sens))

    # if CONF_TEMPERATURE in config:
    #     sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
    #     cg.add(var.set_temperature_sensor(sens))

    # if CONF_AUTOMATIC_BASELINE_CALIBRATION in config:
    #     cg.add(var.set_abc_enabled(config[CONF_AUTOMATIC_BASELINE_CALIBRATION]))


# CALIBRATION_ACTION_SCHEMA = maybe_simple_id(
#     {
#         cv.Required(CONF_ID): cv.use_id(MHZ19Component),
#     }
# )


# @automation.register_action(
#     "mhz19.calibrate_zero", MHZ19CalibrateZeroAction, CALIBRATION_ACTION_SCHEMA
# )
# @automation.register_action(
#     "mhz19.abc_enable", MHZ19ABCEnableAction, CALIBRATION_ACTION_SCHEMA
# )
# @automation.register_action(
#     "mhz19.abc_disable", MHZ19ABCDisableAction, CALIBRATION_ACTION_SCHEMA
# )
# async def mhz19_calibration_to_code(config, action_id, template_arg, args):
#     paren = await cg.get_variable(config[CONF_ID])
#     return cg.new_Pvariable(action_id, template_arg, paren)
