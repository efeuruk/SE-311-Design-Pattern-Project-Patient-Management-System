#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
/*==============================
Ersoy Efe Uruk - 20140601051
Ipek Tekin - 20140601048
Umutcan Berk Hasret - 20150601028
==================================*/
class Person;
class Hospital;

class Mutex{};
class Lock{
public:
    Lock(Mutex& m): mutex(m)
    {
        //cout << "Acquired Lock" << endl;
    }
    ~Lock() {
        //cout << "Releasing Lock" << endl;
    }
private:
    Mutex& mutex;
};

//! Abstract Product-A: Abstract Factory Pattern
//! Singleton Class: Singleton Pattern
//! Command Class 1: Command Pattern
class RadiologicalTest {
protected:
    RadiologicalTest(){};
    RadiologicalTest(const RadiologicalTest&); //! Prevent Copying
    RadiologicalTest& operator = (const RadiologicalTest&); //! Prevent Copying
    static RadiologicalTest* instance;
    static Mutex mutex;

public:
    static RadiologicalTest* getRadiologicalTest(){
        //! Here we are checking if the object has created before.
        if(instance == NULL){
            Lock lock(mutex);
                if(instance == NULL){
                    instance = new RadiologicalTest();
                }
        }
        return instance;

    }
};
Mutex RadiologicalTest:: mutex;
RadiologicalTest *RadiologicalTest::instance = 0;

//! Abstract Product-B: Abstract Factory Pattern
//! Command Class 2: Command Pattern
class LabTest {

};

//! Concrete Product-A1: Abstract Factory Pattern
//! Concrete Command Class 1: Command Pattern
class XRAY : public RadiologicalTest {
public:
    XRAY(string name){cout << "XRAY test for " << name << " is being done."<<  endl;}
};

//! Concrete Product-A2: Abstract Factory Pattern
//! Concrete Command Class 2: Command Pattern
class EKG : public RadiologicalTest {
public:
    EKG(string name){cout << "EKG test for " << name << " is being done."<<  endl;}
};


//! Concrete Product-B1: Abstract Factory Pattern
//! Concrete Command Class 3: Command Pattern
class Cholesterol : public LabTest {
public:
    Cholesterol(string name){cout << "Cholesterol test for " << name << " is being done."<<  endl;}

};

//! Concrete Product-B2: Abstract Factory Pattern
//! Concrete Command Class 4: Command Pattern
class Thyroid : public LabTest {
public:
    Thyroid(string name){cout << "Thyroid test for " << name << " is being done."<<  endl;}

};

//! Abstract Subject: Observer Pattern
class Drug {
private:
    vector<Person*> patients;
    string sideeffect;
    string drug_name;
public:
    Drug(string dname,string seffects) : drug_name(dname),sideeffect(seffects){};
    virtual void SendMessage();
    virtual void Attach(Person* person);
    virtual void Detach(Person* person);
    virtual void setSideEffect(string seffect){
        sideeffect=seffect;
        SendMessage();
        };
    virtual string getSideEffect(){return sideeffect;}
    virtual string getDrugName(){return drug_name;}
};

//! Concrete Subject: Observer Pattern
class Pill: public Drug{
public:
    Pill(string drugname,string seffect):Drug(drugname,seffect){};

};

//! Observer: Observer Pattern
class Person {
protected:
    string name;
public:
    Person(string name) { this->name = name; }
    string getName(){return name;}
    virtual void Update(Drug *drug){};
    virtual void PrescribeMed(Person* person,Drug* drug){};
    virtual void setDepartment(Hospital* dep){};
    virtual void ConductTest(Hospital* dep,Person *patient){};
    virtual Hospital* getDepartment(){};
    virtual void setEmail(string email){};
    virtual void setTelephone(string telephone){};
    virtual string getEmail(){};
    virtual string getTelephone(){};

};

//! ConcreteObserver: Observer Pattern
class Patient : public Person {
private:
    Drug *_drug;
    string drug_s_effect;
    string drug_name;
    string email;
    string telephone;
public:
    Patient(string name): Person(name){};
    void setEmail(string email){this->email=email;}
    void setTelephone(string telephone){this->telephone=telephone;}
    string getEmail(){return email;}
    string getTelephone(){return telephone;}
    void Update(Drug *drug){
        _drug=drug;
        drug_name= drug->getDrugName();
        drug_s_effect= drug->getSideEffect();
        cout<<"\nDue to the side effect change of " << drug_name << " to "<< drug_s_effect << "\n"
        << "Notification mail and SMS sended to following contact adresses; " <<endl;
        cout<< "\n" <<email << "\n" << telephone << endl;
    }

};

//! Abstract Factory Class: Abstract Factory Pattern
//! Abstract Class: Template Method Pattern
class Hospital {
private:
    //!Template Method functions;
    void InsertPDemInf(Person *temp)
    {   string tempemail;
        string tempphone;
        cout<<"PERSONAL DEMOGRAPHIC INFORMATIONS; " << endl;
        cout<<"Insert the following contact information;"<<endl;
        cout<<"E-mail: "; cin >>tempemail;
        cout<<"Telephone: "; cin>>tempphone;
        temp->setEmail(tempemail);
        temp->setTelephone(tempphone);
        cout<<endl<<endl;
    }
    virtual void InsuranceInf(Person *temp){}
    virtual void MedicalHistory(Person *temp){}
    virtual void ConsentForm(Person *temp){}

    vector<Hospital *> Departments;

public:
     //!Template Method
     void CreatePatient(Person *temp){
        InsertPDemInf(temp);
        InsuranceInf(temp);
        MedicalHistory(temp);
        ConsentForm(temp);
    }
    virtual void HireDoctor(Person *doc){};
    void AddDept(Hospital *tdept)
    { Departments.push_back(tdept); }

    virtual RadiologicalTest* CreateRadiologicalTest(Person* patient){};
    virtual LabTest* CreateLabTest(Person* patient){};

};
//! Concrete Factory Class 1: Abstract Factory Pattern
//! Concrete Class 1: Template Method Pattern
//! Receiver Class 1: Command Pattern
class Cardiology : public Hospital {
private:
    void InsuranceInf(Person *temp)
    {   cout<<"INSURANCE MESSAGE" << endl;
        cout<<"Cardiology department accepts only government insurance."<<endl<<endl<<endl;
    }
    void MedicalHistory(Person *temp)
    {   int choice;
        cout<<"MEDICAL HISTORY"<<endl;
        cout<<"Have you ever had cardiac problems before?" << endl;
        cout<<"1 for YES, 0 for NO;" ;
        cin>>choice;
        cout<<"Processing..."<<endl<<endl<<endl;
    }
    void ConsentForm(Person *temp)
    {   int choice;
        cout<<"CONSENT FORM."<<endl;
        cout<<"I have been informed about the conditions and the risks relevant with my treatment under CARDIOLOGY department."<< endl;
        cout<<"I understood and I'm willing to take the risks(PRESS 1) " <<endl;
        cout<<"I understood and I don't want to take the risk(PRESS 0)" <<endl;
        cin>> choice;
        if(choice== 0) exit(0);
        cout<<endl<<endl;

    }
public:
    void HireDoctor(Person *doc){
        doc->setDepartment(this);
    };

    RadiologicalTest* CreateRadiologicalTest(Person* patient){

        return new EKG(patient->getName());
    }
    LabTest* CreateLabTest(Person* patient){
        return new Cholesterol(patient->getName());
    }
};
//! Concrete Factory Class 2 : Abstract Factory Pattern
//! Concrete Class 2: Template Method Pattern
//! Receiver Class 2: Command Pattern
class Endocrinology : public Hospital {
private:
    void InsuranceInf(Person *temp)
    {   cout<<"INSURANCE MESSAGE" << endl;
        cout<<"Endocrinology department doesn't accept any insurance."<<endl<<endl<<endl;
    }
    void MedicalHistory(Person *temp)
    {   int choice;
        cout<<"MEDICAL HISTORY"<<endl;
        cout<<"Have you ever received any kind of hormone treatment before?" << endl;
        cout<<"1 for YES, 0 for NO;" ;
        cin>>choice;
        cout<<"Processing..."<<endl<<endl<<endl;
    }
    void ConsentForm(Person *temp)
    {   int choice;
        cout<<"CONSENT FORM."<<endl;
        cout<<"I have been informed about the conditions and the risks relevant with my treatment under ENDOCRINOLOGY department."<< endl;
        cout<<"I understood and I'm willing to take the risks(PRESS 1) " <<endl;
        cout<<"I understood and I don't want to take the risk(PRESS 0)" <<endl;
        cin>> choice;
        if(choice== 0) exit(0);
        cout<<endl<<endl;
    }
public:
    void HireDoctor(Person *doc){
        doc->setDepartment(this);
    };
    RadiologicalTest* CreateRadiologicalTest(Person* patient){
        return new XRAY(patient->getName());
    }
    LabTest* CreateLabTest(Person* patient){
        return new Thyroid(patient->getName());
    }

};
//! Concrete Factory Class 3 : Abstract Factory Pattern
//! Concrete Class 3: Template Method Pattern
//! Receiver Class 3: Command Pattern
class Orthopedics : public Hospital {
private:
    void InsuranceInf(Person *temp)
    {   cout<<"INSURANCE MESSAGE" << endl;
        cout<<"Orthopedics department accepts only private health insurance."<<endl<<endl<<endl;
    }
     void MedicalHistory(Person *temp)
    {   int choice;
        cout<<"MEDICAL HISTORY"<<endl;
        cout<<"Have you ever had a broken limb before?" << endl;
        cout<<"1 for YES, 0 for NO;" ;
        cin>>choice;
        cout<<"Processing..."<<endl<<endl<<endl;
    }
    void ConsentForm(Person *temp)
    {   int choice;
        cout<<"CONSENT FORM."<<endl;
        cout<<"I have been informed about the conditions and the risks relevant with my treatment under ORTHOPEDICS department."<< endl;
        cout<<"I understood and I'm willing to take the risks(PRESS 1) " <<endl;
        cout<<"I understood and I don't want to take the risk(PRESS 0)" <<endl;
        cin>> choice;
        if(choice== 0) exit(0);
        cout<<endl<<endl;
    }
public:
    void HireDoctor(Person *doc){
        doc->setDepartment(this);
    };
    RadiologicalTest* CreateRadiologicalTest(Person* patient){
        return new XRAY(patient->getName());
    }
};
//!INVOKER CLASS: COMMAND PATTERN && OBJECT DELEGATION FOR ABSTRACT FACTORY.. (Client Class: Abstract Factory)
class LabAttendant{
private:
    RadiologicalTest* _RadiologicalTest;
    LabTest* _LabTest;
    Hospital* temp;
public:
    //! Object creation is delegated to factory
    void CreateTest(Hospital* dep,Person* patient) {
            temp = dep;
            temp->CreateRadiologicalTest(patient);
            temp->CreateLabTest(patient);
    }
};

//! CLIENT FOR COMMAND PATTERN. IT STARTS && MANIPULATES THE TESTING PROCESS..
class Doctor : public Person {
private:
    Hospital* department;
    LabAttendant* medical_test = new LabAttendant();
public:
    Doctor(string name): Person(name){}
    void setDepartment(Hospital* dep){department=dep;}
    Hospital* getDepartment(){return department;}
    //!Ordering Test Function
    void ConductTest(Hospital* department , Person* patient)
    {   medical_test->CreateTest(department,patient); }

    //!Diagnose Function.
    //!Attaching Observer to the Subject Notification Network.
    void PrescribeMed(Person* patient,Drug* drug)
    {   drug->Attach(patient); }
};


void Drug::Attach(Person* person){
    patients.push_back(person);
}
void Drug::Detach(Person* person){
    for (unsigned int i= 0; i< patients.size(); i++) {
		if (patients[i]->getName() == person->getName()) {
			patients.erase(patients.begin()+i);
			return;
		}
	}
}
void Drug::SendMessage(){
    for (unsigned int i = 0; i < patients.size(); i++) {
		patients[i]->Update(this);
	}
}

int main() {
    //! Creating Persons..
    Person* pat1= new Patient("Umutcan Berk HASRET");
    Person* pat2= new Patient("Ipek TEKIN");
    Person* pat3= new Patient("Efe URUK");
    Person* doc1= new Doctor("Dr. Mehmet OZ");
    Person* doc2= new Doctor("Dr. Sukru CANGAR");
    Person* doc3= new Doctor("Dr. Behcet UZ");

    //! Creating Meds..
    Drug* majezik= new Pill("Majezik","Dizzines");
    Drug* aspirine= new Pill("Aspirine","Carpinti");
    Drug* apranax_fort= new Pill("Apranax Fort","Heart Attack");

    //! Creating Hospital && Departments..
    Hospital* Acibadem = new Hospital();
    Hospital* card = new Cardiology();
    Acibadem->AddDept(card);
    Hospital* endo = new Endocrinology();
    Acibadem->AddDept(endo);
    Hospital* ortho = new Orthopedics();
    Acibadem->AddDept(ortho);

    //! Setting Doctors department..
    card->HireDoctor(doc1);
    endo->HireDoctor(doc2);
    ortho->HireDoctor(doc3);

    //! Creating Patients..
    card->CreatePatient(pat1);
    endo->CreatePatient(pat2);
    ortho->CreatePatient(pat3);

    //! Testing Stage..
    doc1->ConductTest(doc1->getDepartment(),pat1);
    doc2->ConductTest(doc2->getDepartment(),pat2);
    doc3->ConductTest(doc3->getDepartment(),pat3);
    cout<<endl<<endl;
    //! Diagnose && Prescribing Pharmaceutical Stage..
    doc1->PrescribeMed(pat1,aspirine);
    doc2->PrescribeMed(pat2,apranax_fort);
    doc3->PrescribeMed(pat3, majezik);

    cout<<endl<<endl;
    //! THE CHANGE OF THE STATE OF THE SIDE EFFECTS..
    aspirine -> setSideEffect("Carpintilar");
    apranax_fort -> setSideEffect("Stroke");
    majezik -> setSideEffect("BlurrySight");




}
