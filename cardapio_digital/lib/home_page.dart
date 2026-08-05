import 'package:flutter/material.dart';
import 'details_page.dart';

class HomePage extends StatelessWidget {
  HomePage({super.key});

  final List<Map<String, dynamic>> pratos = [
    {
      "nome": "Hambúrguer Artesanal",
      "preco": 32.90,
      "descricao": "Pão brioche, carne 180g e queijo cheddar."
    },
    {
      "nome": "Pizza Calabresa",
      "preco": 54.90,
      "descricao": "Pizza grande com bastante queijo."
    },
    {
      "nome": "Lasanha",
      "preco": 39.90,
      "descricao": "Lasanha à bolonhesa gratinada."
    }
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Cardápio Digital"),
        backgroundColor: Colors.red,
      ),
      body: ListView.builder(
        itemCount: pratos.length,
        itemBuilder: (context, index) {
          return Container(
            margin: const EdgeInsets.all(10),
            padding: const EdgeInsets.all(15),
            decoration: BoxDecoration(
              border: Border.all(color: Colors.grey),
              borderRadius: BorderRadius.circular(10),
            ),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      pratos[index]["nome"],
                      style: const TextStyle(
                          fontSize: 20, fontWeight: FontWeight.bold),
                    ),
                    Text("R\$ ${pratos[index]["preco"]}"),
                  ],
                ),
                ElevatedButton(
                  child: const Text("Ver"),
                  onPressed: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (_) => DetailsPage(
                          prato: pratos[index],
                        ),
                      ),
                    );
                  },
                )
              ],
            ),
          );
        },
      ),
    );
  }
}