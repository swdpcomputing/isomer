#pragma once
#include "IsomerObject.h"

class IsomerVTU :   public ValueTree::Listener
{
    public:
        IsomerVTU() 
        {
            mainVT->addListener (this);
        };
    
        virtual ~IsomerVTU()
        {
            mainVT->removeListener (this);
        };

        virtual void updateValueTree() {}; // For updating the ValueTree when loading a save file
        virtual void postUpdateValueTree() {}; // Initialise any post update instructions
        
    protected:
        static ScopedPointer <UndoManager> undoManager;
        static ScopedPointer <ValueTree> mainVT;

        ValueTree thisVT;  
        
        void valueTreePropertyChanged (ValueTree&, const Identifier&) override {};
        void valueTreeChildAdded (ValueTree&, ValueTree&) override {};
 	    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override {};
 	    void valueTreeChildOrderChanged (ValueTree&, int, int) override {};
 	    void valueTreeParentChanged (ValueTree&) override {};
 	    void valueTreeRedirected (ValueTree&) override {};
        
        virtual void updateVTProperties() {}; // Update the properties from the updated ValueTree
        
            //-----VALUETREE FUNCTIONS-----\\
        
        static StringArray getAllPropertyIds (ValueTree a)
        {
            StringArray sa;
            for (int i = 0; i < a.getNumProperties(); ++i) sa.add (a.getPropertyName (i).toString());
            return sa;
        }
        
        static StringArray getAllChildIds (ValueTree a)
        {
            StringArray sa;
            for (int i = 0; i < a.getNumChildren(); ++i) sa.add (a.getChild (i).getType().toString());
            return sa;
        }
        
        static void printAllChildIds (ValueTree a)
        {
            StringArray sa = getAllChildIds (a);
            printStringArray (sa);
        }
        
        static void printAllProperties (ValueTree a)
        {
            StringArray sa = getAllPropertyIds (a);
            printPropertyIDArray (sa);
        }
        
        static void printTree (ValueTree a)
        {
            DBG ("---" << a.getType().toString());
            if (a.getNumProperties() > 0) printAllProperties (a);
                        
            if (a.getNumChildren() > 0)
            {
                StringArray sa = getAllChildIds (a);
                for (auto& o : sa) printTree (a.getChildWithName (o));
            };
        }
        
        static void printVarArray (const Array <var>& a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "Var at index " << a.indexOf (obj) << " : " << obj.toString() << std::endl;
        }

        static void printVarArray (const var a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (int i = 0; i < a.size(); ++i) std::cout << "Var at index " << i << " : " << a[i].toString() << std::endl;
        }
        
        static void printStringArray (const StringArray& a)
        {
            for (auto obj : a) std::cout << obj << std::endl;
        }
        
        static void printStringArrayWithSize (const StringArray& a)
        {
            std::cout << "StringArray Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "String at index " << a.indexOf (obj) << " " << obj << std::endl;
        }
        
        static void printPropertyIDArray (const StringArray& a)
        {
            DBG ("     Properties");
            for (auto obj : a) std::cout << " - " << obj << std::endl;
        }
        
        static void printIntArray (const Array <int>& a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "Integer at index " << a.indexOf (obj) << " : " << String (obj) << std::endl;
        }

        static void printFloatArray (const Array <float>& a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "Float at index " << a.indexOf (obj) << " : " << String (obj) << std::endl;
        }

        static void printDoubleArray (const Array <double>& a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "Double at index " << a.indexOf (obj) << " : " << String (obj) << std::endl;
        }
    
        static void printBoolArray (const Array <bool>& a)
        {
            std::cout << "Array Size: " << a.size() << std::endl;
            for (auto obj : a) std::cout << "Bool at index " << a.indexOf (obj) << " : " << obj << std::endl;
        }  
        
        static var arrIntToVar (const Array <int>& aI)
        {
            var v;
            for (auto o : aI) v.append (var (o));
            return v;
        }

        static var arrDoubleToVar (const Array <double>& aI)
        {
            var v;
            for (auto o : aI) v.append (var (o));
            return v;
        }

        static var strArrToVar (const StringArray& a)
        {
            var v;
            for (auto o : a) v.append (var (o));
            return v;
        }

        static Array <int> varToArrInt (var v)
        {
            Array <int> aI;
            for (int i = 0; i < v.size(); ++i) aI.add (v [i]);
            return aI;
        }

        static Array <double> varToArrDouble (var v)
        {
            Array <double> aI;
            for (int i = 0; i < v.size(); ++i) aI.add (v [i]);
            return aI;
        }

        static StringArray varToStrArr (var v)
        {
            StringArray sa;
            for (int i = 0; i < v.size(); ++i) sa.add (v [i].toString());
            return sa;
        }
        
            //-----VALUETREE GET FUNCTIONS-----\\
            
        static const int getMasterKeyNum()
        {
            return mainVT->getChildWithName ("guiVT").getChildWithName ("masterSection").getProperty ("masterKeyNum").operator int();
        }
};