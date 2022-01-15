//
// Created by majga on 20.12.2021.
//

#ifndef ZPO_SIECI_FACTORY_HPP
#define ZPO_SIECI_FACTORY_HPP
#include "types.hpp"
#include "nodes.hpp"
#include <sstream>


enum class NodeColor
{ UNVISITED, VISITED, VERIFIED};

template <typename Node>
class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    //iteratory
    iterator begin() {return _container.begin();}
    iterator end() {return _container.end();}
    const_iterator begin() const {return _container.cbegin();}
    const_iterator cbegin() const {return _container.cbegin();}
    const_iterator end() const {return _container.cend();}
    const_iterator cend() const {return _container.cend();}

    //Wyszukiwanie po ID
    NodeCollection<Node>::iterator find_by_id(ElementID id){return std::find_if(_container.begin(),_container.end(),[id](const auto& i){return id == i.get_id();});}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {return std::find_if(_container.cbegin(),_container.cend(),[id](const auto& i){return id == i.get_id();});}
    //Usuwanie
    void remove_by_id(ElementID id){
        auto iter = find_by_id(id);
        if(iter != _container.end()){ //Sprawdzenie czy element został znaleziony..
            _container.erase(iter);
        }
    }
    void add(Node& node){_container.push_back(std::move(node));}



private:
    container_t _container;
};





class Factory{
public:
    //Ramp
    void add_ramp(Ramp&& rmp){_ramp.add(rmp);}
    void remove_ramp(ElementID id){_ramp.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){return _ramp.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return _ramp.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return _ramp.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return _ramp.cend();}
    //Storehouse
    void add_storehouse(Storehouse&& str){_storehouse.add(str);}
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){return _storehouse.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return _storehouse.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return _storehouse.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return _storehouse.cend();}

    //worker
    void add_worker(Worker&& wrk){_worker.add(wrk);}
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){return _worker.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return _worker.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worek_cbegin() const {return _worker.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return _worker.cend();}
    //logika biznesowa
    bool is_consistent(void);
    void do_deliveries(Time);
    void do_package_passing(void);
    void do_work(Time);










private:
    NodeCollection<Ramp> _ramp;
    NodeCollection<Storehouse> _storehouse;
    NodeCollection<Worker> _worker;




};

enum class ElementType{
    RAMP,WORKEK,STOREHOUSE, LINK
};
struct ParsedLineData{
    ElementType element_type;
    std::map<std::string,std::string> parameters;
};
ParsedLineData parse_line(const std::string& line);
Factory load_factory_structure(std::istream& is);
void save_factory_structure(Factory& factory, std::ostream& os);




#endif //ZPO_SIECI_FACTORY_HPP