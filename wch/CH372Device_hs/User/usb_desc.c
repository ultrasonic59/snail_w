/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : usb device descriptor,configuration descriptor,
 *                      string descriptors and other descriptors.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "usb_desc.h"

/* Device Descriptor */
const uint8_t  MyDevDescr[ ] =
{
    0x12,       // bLength
    0x01,       // bDescriptorType (Device)
    0x00, 0x02, // bcdUSB 2.00
    0xFF,       // bDeviceClass
    0xFF,       // bDeviceSubClass
    0xFF,       // bDeviceProtocol
    DEF_USBD_UEP0_SIZE,   // bMaxPacketSize0 64
    (uint8_t)DEF_USB_VID, (uint8_t)(DEF_USB_VID >> 8),  // idVendor 0x1A86
    (uint8_t)DEF_USB_PID, (uint8_t)(DEF_USB_PID >> 8),  // idProduct 0x5537
    DEF_IC_PRG_VER, 0x00, // bcdDevice 0.01
    0x01,       // iManufacturer (String Index)
    0x02,       // iProduct (String Index)
    0x03,       // iSerialNumber (String Index)
    0x01,       // bNumConfigurations 1
};

/* USBÅäÖÃÃèÊö·û(¸ßËÙ) */
const uint8_t  MyCfgDescr_HS[ ] =
{
    0x09,        // bLength
    0x02,        // bDescriptorType (Configuration)
    RHID_SIZ_CONFIG_DESC, 0x00,  // wTotalLength 60
    0x01,        // bNumInterfaces 1
    0x01,        // bConfigurationValue
    0x00,        // iConfiguration (String Index)
    0x80,        // bmAttributes
    0x32,        // bMaxPower 100mA

    0x09,        // bLength
    0x04,        // bDescriptorType (Interface)
    0x00,        // bInterfaceNumber 0
    0x00,        // bAlternateSetting
    0x02,        // bNumEndpoints 2 ///6
    0x03,        // bInterfaceClass
    0x00,        // bInterfaceSubClass
    0x00,        // bInterfaceProtocol
    0x00,        // iInterface (String Index)
    /******************** HID ********************/
    0x09,         // bLength:
    HID_DESCRIPTOR_TYPE, // bDescriptorType:  - HID
    0x01, 0x01,   // bcdHID:  HID 1.1
    0x00,         // bCountryCode:
    0x01,         // bNumDescriptors:  report
    HID_REPORT_DESCRIPTOR_TYPE,         // bDescriptorType: - report
    RHID_SIZ_REPORT_DESC,   0x00, // wItemLength: report-

    0x07,        // bLength
    USB_ENDPOINT_DESCRIPTOR_TYPE,        // bDescriptorType (Endpoint)
    0x81,        // bEndpointAddress (OUT/H2D)
    0x03,        // bmAttributes (Interrupt endpoint)
    (uint8_t)DEF_USB_EP1_HS_SIZE, (uint8_t)( DEF_USB_EP1_HS_SIZE >> 8 ), // wMaxPacketSize 8
    0x20,        // bInterval 0 (unit depends on device speed)

    0x07,        // bLength
    USB_ENDPOINT_DESCRIPTOR_TYPE,        // bDescriptorType (Endpoint)
    0x01,        // bEndpointAddress (IN/D2H)
    0x03,        // bmAttributes (Interrupt endpoint)
    (uint8_t)DEF_USB_EP2_HS_SIZE, (uint8_t)( DEF_USB_EP2_HS_SIZE >> 8 ),  // wMaxPacketSize 8
    0x20,        // bInterval 0 (unit depends on device speed)
};

/* Configuration Descriptor */
const uint8_t  MyCfgDescr_FS[ ] =
{
    0x09,        // bLength
    0x02,        // bDescriptorType (Configuration)
    RHID_SIZ_CONFIG_DESC, 0x00,  // wTotalLength 60
    0x01,        // bNumInterfaces 1
    0x01,        // bConfigurationValue
    0x00,        // iConfiguration (String Index)
    0x80,        // bmAttributes
    0x32,        // bMaxPower 100mA

    0x09,        // bLength
    0x04,        // bDescriptorType (Interface)
    0x00,        // bInterfaceNumber 0
    0x00,        // bAlternateSetting
    0x02,        // bNumEndpoints 2
    0x03,        // bInterfaceClass
    0x00,        // bInterfaceSubClass
    0x00,        // bInterfaceProtocol
    0x00,        // iInterface (String Index)
    /******************** HID ********************/
    0x09,         // bLength:
    HID_DESCRIPTOR_TYPE, // bDescriptorType:  - HID
    0x01, 0x01,   // bcdHID:  HID 1.1
    0x00,         // bCountryCode:
    0x01,         // bNumDescriptors:  report
    HID_REPORT_DESCRIPTOR_TYPE,         // bDescriptorType: - report
    RHID_SIZ_REPORT_DESC,   0x00, // wItemLength: report-

    0x07,        // bLength
    0x05,        // bDescriptorType (Endpoint)
    0x81,        // bEndpointAddress (OUT/H2D)
    0x03,        // bmAttributes (Bulk)
    (uint8_t)DEF_USB_EP1_FS_SIZE, (uint8_t)( DEF_USB_EP1_FS_SIZE >> 8 ), // wMaxPacketSize 8
    0x00,        // bInterval 0 (unit depends on device speed)

    0x07,        // bLength
    0x05,        // bDescriptorType (Endpoint)
    0x01,        // bEndpointAddress (IN/D2H)
    0x03,        // bmAttributes (Bulk)
    (uint8_t)DEF_USB_EP2_FS_SIZE, (uint8_t)( DEF_USB_EP2_FS_SIZE >> 8 ),  // wMaxPacketSize 8
    0x00        // bInterval 0 (unit depends on device speed)
};
const uint8_t RHID_ReportDescriptor[RHID_SIZ_REPORT_DESC] =
  {
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0xb1, 0x82,                    //   FEATURE (Data,Var,Abs,Vol)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)

    0x85, 0x02,                    //   REPORT_ID (2)
    0x09, 0x02,                    //   USAGE (Vendor Usage 2)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0xb1, 0x82,                    //   FEATURE (Data,Var,Abs,Vol)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x09, 0x02,                    //   USAGE (Vendor Usage 2)
    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)

    0x85, 0x03,                    //   REPORT_ID (3)
    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, RPT3_COUNT,                    //   REPORT_COUNT (N)
    0xb1, 0x82,                    //   FEATURE (Data,Var,Abs,Vol)
    0x85, 0x03,                    //   REPORT_ID (3)
    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)

    0x85, 0x04,                    //   REPORT_ID (4)
    0x09, 0x04,                    //   USAGE (Vendor Usage 4)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, RPT4_COUNT,                    //   REPORT_COUNT (N)
    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
    0xc0                           // END_COLLECTION
};

/* Language Descriptor */
const uint8_t  MyLangDescr[] =
{
    0x04, 0x03, 0x09, 0x04
};

/* Manufacturer Descriptor */
const uint8_t  MyManuInfo[] =
{
    0x0C, 0x03, 's', 0, 'n', 0, 'a', 0, 'i', 0, 'l', 0
};

/* Product Information */
const uint8_t  MyProdInfo[] =
{
    0x10, 0x03, 'S', 0, 'N', 0, '-', 0, 'H', 0, 'I', 0, 'D', 0

};

/* Serial Number Information */
const uint8_t  MySerNumInfo[] =
{
    0x16, 0x03, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '5', 0
              , '6', 0, '7', 0, '8', 0, '9', 0
};

/* Device Qualified Descriptor */
const uint8_t MyQuaDesc[ ] =
{
    0x0A, 0x06, 0x00, 0x02, 0xFF, 0xFF, 0xFF, 0x40, 0x01, 0x00,
};

/* Device BOS Descriptor */
const uint8_t MyBOSDesc[ ] =
{
    0x05, 0x0F, 0x0C, 0x00, 0x01,
    0x07, 0x10, 0x02, 0x02, 0x00, 0x00, 0x00,
};

/* USB Full-Speed Mode, Other speed configuration Descriptor */
uint8_t TAB_USB_FS_OSC_DESC[ sizeof(MyCfgDescr_HS) ] =
{
    /* Other parts are copied through the program */
    0x09, 0x07,
};

/* USB High-Speed Mode, Other speed configuration Descriptor */
uint8_t TAB_USB_HS_OSC_DESC[ sizeof(MyCfgDescr_FS) ] =
{
    /* Other parts are copied through the program */
    0x09, 0x07,
};
