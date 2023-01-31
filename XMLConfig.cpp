
// Created by cuadriante on 3/11/21.


#include "XMLConfig.h"

XMLConfig::XMLConfig(vector<Individual *> searchSpace, int genomeSize, int generation) {


    for(int i = 0; i < searchSpace.size(); i++){
        Individual* individual = searchSpace.at(i);
        child.add("Id", i + 1);
        child.add("fitness", individual->getFitness());
//        for(int i = 0; i < genomeSize; i++){
//            //child.add("gene" + to_string(i), individual->getGene(i));
//        }
        pt.add_child("population.individual", child);
        child.clear();
    }
    //boost::property_tree::xml_parser::write_xml("XML/generation" + to_string(generation) + ".xml", pt);
}

void XMLConfig::clearFile() {
    pt.clear();
}
