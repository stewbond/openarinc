#ifndef OPENARINC_A429BASE_HPP
#define OPENARINC_A429BASE_HPP

namespace a429
{
    typedef unsigned int UINT;
    typedef unsigned char UCHAR;

    // Base class for A429 objects
    // It provides common methods for manipulating the word
    class a429base
    {
    private:
        UINT m_myword;        // Local label used if constructed by value
    protected:
        UINT* m_packed;        // Points to m_myword if constructed by value, or the origin if constructed by reference

    public:
        // Constructors
        a429base();                        // Default constructor (initializes to zero'd internal memory)
        a429base(const a429base& copy);    // Copy constructor
        a429base(UINT input);              // Construct by value, (initializes to internal memory with the input value)
        a429base(UINT* reference);         // Construct to a refernce (intializes to utilize external memory, see Link() ).

        ~a429base();

        // Casting/Operating
        operator UINT() const { return *m_packed; }
        UINT operator= (UINT word);

        // Which memory?
        a429base& Link(UINT* word);    // Uses the linked pointer as memory, any manipulation done by this class will affect that memory.
        a429base& UnLink();            // De-links the object and points to its own internal memory

        // Common A429 utilities
        a429base& SetSDI(UCHAR value);     // Self-descriptive, set 0-3
        a429base& SetSSM(UCHAR value);     // Self-descriptive, set 0-3
        a429base& SetLbl(UCHAR value);     // Sets the label name from an octal number, Ex: SetLbl(0270) will set label 270 (0x1d)
        a429base& SetRevLbl(UCHAR value);  // Sets the label name from a direct byte, Ex: SetRevLbl(0x1d) will set label 0270
        a429base& SetPar();                // Auto-sets the parity of the label
        a429base& SetPar(bool p);          // Allows the user to drive the parity bit of the label

        UCHAR GetSDI()    const;  // Returns the SDI (bits 9-10)
        UCHAR GetSSM()    const;  // Returns the SSM (bits 30-31)
        UCHAR GetLbl()    const;  // Returns the label (ex: 0270)
        UCHAR GetRevLbl() const;  // Returns the reversed packed label (bits 1-9)(ex: 0x1d)
        UCHAR GetPar()    const;  // Returns the parity bit (bit 32)
        UINT  GetWord()   const;  // Returns the entire A429 word

        UCHAR CalcPar()   const;  // Calculates the appropriate parity bit of the A429 word.
    };
}
#endif // OPENARINC_A429BASE_HPP

