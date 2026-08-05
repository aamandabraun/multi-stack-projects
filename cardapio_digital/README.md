# 🍽️ Cardápio Digital de Restaurante

## 📖 Sobre o projeto

O **Cardápio Digital de Restaurante** é um aplicativo desenvolvido em **Flutter** como atividade da disciplina de Desenvolvimento de Sistemas Web.

O objetivo do aplicativo é permitir que o usuário visualize os pratos disponíveis em um restaurante, acesse os detalhes de cada item do cardápio e selecione a quantidade desejada para simular um pedido.

---

## 🎯 Objetivos

* Desenvolver uma interface utilizando Flutter.
* Aplicar conceitos de navegação entre telas.
* Utilizar gerenciamento de estado com `StatefulWidget` e `setState()`.
* Organizar a interface utilizando os widgets `Scaffold`, `Row`, `Column` e `Container`.

---

## ✨ Funcionalidades

* 📋 Listagem de pratos disponíveis.
* 🔎 Tela de detalhes de cada prato.
* ➕ Aumentar a quantidade do pedido.
* ➖ Diminuir a quantidade do pedido.
* 💲 Atualização automática do valor total.
* 🔙 Retorno para a tela inicial.

---

## 📱 Estrutura do aplicativo

### Tela Inicial

* Lista dos pratos disponíveis.
* Exibe nome e preço.
* Botão **"Ver"** para acessar os detalhes.

### Tela de Detalhes

* Nome do prato.
* Descrição.
* Preço.
* Controle de quantidade.
* Valor total calculado automaticamente.
* Botão para voltar à tela inicial.

---

## 🛠️ Tecnologias utilizadas

* Flutter
* Dart
* Visual Studio Code

---

## 📂 Estrutura do projeto

```text
lib/
├── main.dart
├── home_page.dart
└── details_page.dart
```

---

## 📌 Requisitos atendidos

* ✅ Duas telas distintas.
* ✅ Navegação utilizando `Navigator.push()`.
* ✅ Retorno utilizando `Navigator.pop()`.
* ✅ Uso de `Scaffold` em ambas as telas.
* ✅ Interface construída com `Row`, `Column` e `Container`.
* ✅ Funcionalidade dinâmica utilizando `StatefulWidget`.
* ✅ Atualização da interface com `setState()`.

---

## ▶️ Como executar o projeto

1. Clone este repositório:

```bash
git clone https://github.com/SEU-USUARIO/cardapio-digital.git
```

2. Entre na pasta do projeto:

```bash
cd cardapio-digital
```

3. Instale as dependências:

```bash
flutter pub get
```

4. Execute o aplicativo:

```bash
flutter run
```