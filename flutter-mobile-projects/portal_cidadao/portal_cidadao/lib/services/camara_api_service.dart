import 'package:dio/dio.dart';

import '../models/despesa.dart';
import '../models/politico.dart';
import '../models/proposicao.dart';

/// Exceção de domínio lançada pela camada de serviço, para que as Views
/// tratem falhas de rede sem precisar conhecer detalhes do Dio.
class ApiException implements Exception {
  final String message;
  ApiException(this.message);

  @override
  String toString() => message;
}

/// Camada única de consumo da API de Dados Abertos da Câmara dos
/// Deputados. Nenhuma View deve chamar `Dio` diretamente — tudo passa
/// por aqui, mantendo a separação de responsabilidades exigida pela
/// arquitetura MVC/MVVM do projeto.
class CamaraApiService {
  CamaraApiService._internal();
  static final CamaraApiService instance = CamaraApiService._internal();

  final Dio _dio = Dio(
    BaseOptions(
      baseUrl: 'https://dadosabertos.camara.leg.br/api/v2',
      connectTimeout: const Duration(seconds: 15),
      receiveTimeout: const Duration(seconds: 15),
      headers: {'accept': 'application/json'},
    ),
  );

  /// Lista parlamentares em exercício, com filtros opcionais de
  /// UF e partido e suporte a paginação (usado pelo Lazy Loading da
  /// listagem principal).
  Future<List<Politico>> listarPoliticos({
    String? uf,
    String? partido,
    int pagina = 1,
    int itensPorPagina = 30,
  }) async {
    try {
      final response = await _dio.get(
        '/deputados',
        queryParameters: {
          if (uf != null && uf.isNotEmpty) 'siglaUf': uf,
          if (partido != null && partido.isNotEmpty) 'siglaPartido': partido,
          'pagina': pagina,
          'itens': itensPorPagina,
          'ordem': 'ASC',
          'ordenarPor': 'nome',
        },
      );

      final dados = response.data['dados'] as List<dynamic>? ?? [];
      return dados
          .map((json) => Politico.fromJson(json as Map<String, dynamic>))
          .toList();
    } on DioException catch (e) {
      throw ApiException(_mensagemDeErro(e));
    } catch (e) {
      throw ApiException('Erro inesperado ao carregar parlamentares: $e');
    }
  }

  Future<Politico> buscarDetalhePolitico(int id) async {
    try {
      final response = await _dio.get('/deputados/$id');
      return Politico.fromDetailJson(response.data as Map<String, dynamic>);
    } on DioException catch (e) {
      throw ApiException(_mensagemDeErro(e));
    }
  }

  /// Retorna as despesas do parlamentar, opcionalmente filtradas por
  /// ano/mês, ordenadas da mais recente para a mais antiga.
  Future<List<Despesa>> listarDespesas(
    int idPolitico, {
    int? ano,
    int? mes,
    int pagina = 1,
    int itensPorPagina = 50,
  }) async {
    try {
      final response = await _dio.get(
        '/deputados/$idPolitico/despesas',
        queryParameters: {
          if (ano != null) 'ano': ano,
          if (mes != null) 'mes': mes,
          'pagina': pagina,
          'itens': itensPorPagina,
          'ordem': 'DESC',
          'ordenarPor': 'dataDocumento',
        },
      );

      final dados = response.data['dados'] as List<dynamic>? ?? [];
      return dados
          .map((json) => Despesa.fromJson(json as Map<String, dynamic>))
          .toList();
    } on DioException catch (e) {
      throw ApiException(_mensagemDeErro(e));
    }
  }

  Future<List<Proposicao>> listarProposicoes(int idPolitico) async {
    try {
      final response = await _dio.get(
        '/proposicoes',
        queryParameters: {
          'idDeputadoAutor': idPolitico,
          'ordem': 'DESC',
          'ordenarPor': 'id',
          'itens': 30,
        },
      );

      final dados = response.data['dados'] as List<dynamic>? ?? [];
      return dados
          .map((json) => Proposicao.fromJson(json as Map<String, dynamic>))
          .toList();
    } on DioException catch (e) {
      throw ApiException(_mensagemDeErro(e));
    }
  }

  String _mensagemDeErro(DioException e) {
    switch (e.type) {
      case DioExceptionType.connectionTimeout:
      case DioExceptionType.receiveTimeout:
        return 'Tempo de conexão esgotado. Verifique sua internet e tente novamente.';
      case DioExceptionType.connectionError:
        return 'Sem conexão com a internet. Consulte seus favoritos salvos offline.';
      case DioExceptionType.badResponse:
        return 'A API da Câmara retornou um erro (HTTP ${e.response?.statusCode}).';
      default:
        return 'Não foi possível carregar os dados no momento.';
    }
  }
}
