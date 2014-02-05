#ifndef GS_GRID_H
#define GS_GRID_H

#include <string>
#include <functional>
#include <vector>
#include <complex>

namespace gw
{
  class named
  {
    std::string m_Name;
    public:
      //named(std::string Name) : m_Name{Name} {}
      named(std::string &&Name) : m_Name{Name} {}
      named(const char *Name) : m_Name{Name} {}

      std::string Name() const { return m_Name; }
  };

  
  class equipment 
  {
    public:
      enum class type
      {
        bus,
        transformer,
        line
      };

    private:
      type m_Type;

    public:
      equipment(type Type) : m_Type{Type} {}

      type Type() const { return m_Type; }
  };


  template <size_t n>
  class rated_equipment : public equipment
  {
    std::array<double, n> m_Ratings;
    public:
      rated_equipment(type Type, std::array<double, n> && Ratings)
        : equipment{Type}, m_Ratings(Ratings)
      {}
  };
  
  class bus : public rated_equipment<1>
  {
    public:
      std::string Name{""};   
      bus(std::string Name, double Rating) 
        : rated_equipment{type::bus, {Rating}}, 
          Name{Name} {}
  };
  
  class branch
  {
    public:
      std::string Name{""};
      bus *BusA, *BusB;
      std::complex<double> Z;

      branch(std::string Name, bus *BusA, bus *BusB,
          std::complex<double> Z)
        : Name{Name}, BusA{BusA}, BusB{BusB}, Z{Z} {}
  };
  
  class line : public branch, public rated_equipment<1>
  {
    public:
      line(std::string Name, bus *BusA, bus *BusB,
          std::complex<double> Z, double KvRating)
        : rated_equipment{type::line, {KvRating}},
          branch{Name, BusA, BusB, Z} {}
  };
  
  class transformer : public branch, public rated_equipment<2>
  {
    public:
      std::complex<double> T;

      transformer(std::string Name, bus *BusA, bus *BusB, 
          std::complex<double> Z, std::complex<double> T, 
          double LowKvRating, double HighKvRating )
        : rated_equipment{type::transformer, {LowKvRating, HighKvRating}},
          branch(Name, BusA, BusB, Z), T{T} {}
  };


  class equipment_container
  {
    std::vector<equipment*> m_Equipment;

    public:
      bus* AddBus(std::string Name, double Rating)
      {
        bus *bp = new bus(Name, Rating);
        m_Equipment.push_back(bp);
        return bp;
      }

      transformer* AddTransformer(std::string Name, bus *A, bus *B,
          std::complex<double> Z, std::complex<double> T,
          double LKVR, double HKVR)
      {
        transformer *tp = new transformer(Name, A, B, Z, T, LKVR, HKVR);
        m_Equipment.push_back(tp);
        return tp;
      }


      //TODO: Clean up your shit
      ~equipment_container()
      {

      }
  };
  
  class substation : public named, public equipment_container
  {
    public:
      using named::named;
  };

  class grid : named
  {
    std::vector<substation*> m_Substations;
    std::vector<line*> m_Lines;

    public: 
      using named::named;

      substation* 
      AddSubstation(std::string &&Name) 
      { 
        substation *sp = new substation(std::move(Name));
        m_Substations.push_back(sp);
        return sp;
      }
      
      line* 
      AddLine(std::string Name, bus *A, bus *B, std::complex<double> Z, 
              double KVR)
      {
        line *lp = new line(Name, A, B, Z, KVR);
        m_Lines.push_back(lp);
        return lp;
      }
  };

}//namespace gw

#endif
