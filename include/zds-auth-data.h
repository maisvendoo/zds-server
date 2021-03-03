#ifndef     ZDS_AUTH_DATA_H
#define     ZDS_AUTH_DATA_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#pragma pack(push, 1)

struct zds_auth_data_t
{
    unsigned char   id;
    unsigned short  train_number;
    unsigned short  route_trk_num;
    unsigned short  unknown1;
    unsigned short  unknown2;
    unsigned short  loco_type;
    unsigned char   loco_service_type;
    unsigned char   carriges_number;

    zds_auth_data_t()
        : id(1)
        , train_number(0)
        , route_trk_num(0)
        , unknown1(0)
        , unknown2(0)
        , loco_type(0)
        , loco_service_type(0)
        , carriges_number(0)
    {

    }
};

#pragma pack(pop)

#endif // ZDS_AUTH_DATA_H
