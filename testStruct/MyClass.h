#include <QObject>
#include <QDebug>
using namespace std;



#define QML_WRITABLE_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name WRITE set_##name MEMBER m_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    void set_##name (type name) { \
        m_##name = name; \
        emit name##Changed (m_##name); \
    } \
    Q_SIGNALS: \
        void name##Changed (type name);




struct MyStruct {
    Q_GADGET
    int m_val;
    QString m_name1;
    QString m_name2;
    QString m_name3;
    QString m_name4;
    Q_PROPERTY(int val MEMBER m_val READ getVal WRITE setVal)
    Q_PROPERTY(QString name1 READ getName1 WRITE setName1 MEMBER m_name1)

    Q_PROPERTY(QString name2 MEMBER m_name2)
    Q_PROPERTY(QString name3 MEMBER m_name3)
    Q_PROPERTY(QString name4 MEMBER m_name4)

public:

    QString getName1() {
        return m_name1;
    }

    void setName1(QString name) {
        m_name1 = name;
    }


    int getVal() {
        return m_val;
    }

    void setVal(int value) {
        m_val = value;
    }
};





struct VehicleInfoStruct {
    Q_GADGET

    bool m_vehicle_CD;
    QString m_bodyType;

    Q_PROPERTY(bool vehicle_CD READ getVehicle_CD WRITE setVehicle_CD MEMBER m_vehicle_CD)
    Q_PROPERTY(QString bodyType READ getBodyType WRITE setBodyType MEMBER m_bodyType)

public:
    VehicleInfoStruct() {
        m_vehicle_CD = false;
        m_bodyType = "";

    }



    VehicleInfoStruct& operator =(const VehicleInfoStruct& a)
    {

        m_vehicle_CD = a.m_vehicle_CD;
        m_bodyType = a.m_bodyType;
        return *this;
    }


    bool getVehicle_CD() {
        return m_vehicle_CD;
    }

    void setVehicle_CD(bool isCDVehicle) {
        if (m_vehicle_CD != isCDVehicle) {
            m_vehicle_CD = isCDVehicle;
        }
    }

    QString getBodyType() {
        return m_bodyType;
    }

    void setBodyType(QString isCDVehicle) {
            m_bodyType = isCDVehicle;
    }

};

struct DefaultStruct {
    Q_GADGET

    struct VehicleInfoStruct mVehicleInfo;
    Q_PROPERTY(VehicleInfoStruct vehicleInfo READ getVehicleInfo WRITE setVehicleInfo MEMBER mVehicleInfo)


    QString mFullDescription;
    Q_PROPERTY(QString fullDescription READ getFullDescription WRITE setFullDescription MEMBER mFullDescription)

    int mDataValue;
    Q_PROPERTY(int dataValue READ getDataValue WRITE setDataValue MEMBER mDataValue)

public:
    DefaultStruct() {
            mVehicleInfo.setBodyType("dldyddn_Body");
            mVehicleInfo.setVehicle_CD("true");

            setFullDescription("qqqqqqqqqqqq");
    }

    // operator
    DefaultStruct& operator =(const DefaultStruct& a)
    {
        mVehicleInfo = a.mVehicleInfo;

        mFullDescription = a.mFullDescription;

        return *this;
    }


    //getter
    VehicleInfoStruct getVehicleInfo(){

        qDebug() << "======== get Data : " << mVehicleInfo.getBodyType() << "-"<< mVehicleInfo.getVehicle_CD();
        return mVehicleInfo;
    }

    QString getFullDescription() {
        return mFullDescription;
    }

    int getDataValue() {
        return mDataValue;
    }


    //setter
    void setVehicleInfo(VehicleInfoStruct str) {
        qDebug() << "Input Data : " << str.getBodyType() << "-"<< str.getVehicle_CD();
        qDebug() << "Prev Data : " << mVehicleInfo.getBodyType() << "-"<< mVehicleInfo.getVehicle_CD();
        mVehicleInfo = str;
        qDebug() << "Update Data : " << mVehicleInfo.getBodyType() << "-"<< mVehicleInfo.getVehicle_CD();
    }

    void setFullDescription (QString value) {
        mFullDescription = value;
    }

    void setDataValue (int value) {
        mDataValue = value;
    }

public:


};

class MyClass:public QObject
{
    Q_OBJECT
    Q_PROPERTY(MyStruct mystr READ getMyStruct
               WRITE setMyStruct NOTIFY myStructChanged)

    Q_PROPERTY(DefaultStruct mystr2 READ getMyStruct2
               WRITE setMyStruct2 )

//    QML_WRITABLE_PROPERTY(int, dldyddn)

//    QML_WRITABLE_PROPERTY(MyStruct, myStr)

public:
    explicit MyClass(QObject *parent = nullptr){
        qRegisterMetaType<MyStruct>("MyStruct");

        qRegisterMetaType<DefaultStruct>("DefaultStruct");
        qRegisterMetaType<VehicleInfoStruct>("VehicleInfoStruct");


        strObj.setName1("test");
        strObj.setVal(22);

        setMyStruct(strObj);


    };
    MyStruct strObj;

    // Edit: changed get function
    MyStruct getMyStruct() const
    {
        return strObj;
    }

    // Edit: Added set function
    void setMyStruct(MyStruct val)
    {
        strObj = val;
        emit myStructChanged();
    }

    DefaultStruct strObj2;

    DefaultStruct getMyStruct2() const
    {
        return strObj2;
    }

    // Edit: Added set function
    void setMyStruct2(DefaultStruct val)
    {
        strObj2 = val;
    }


signals:
    void myStructChanged();

};


